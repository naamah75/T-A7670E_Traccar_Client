#include "communication.h"

#include "util.h"

Communication::Communication(TinyGsm* modem, TinyGsmClient* client, Settings* config)
{
    m_modem = modem;
    m_client = client;
    m_config = config;

    pinMode(BOARD_POWERON_PIN, OUTPUT);
    pinMode(MODEM_POWER_PIN, OUTPUT);
    pinMode(MODEM_RESET_PIN, OUTPUT);
    digitalWrite(BOARD_POWERON_PIN, HIGH);
    digitalWrite(MODEM_POWER_PIN, LOW);
    digitalWrite(MODEM_RESET_PIN, LOW);
}

bool Communication::init(ota::status ota_status)
{
    MODEM_SERIAL.begin(MODEM_BAUDRATE, SERIAL_8N1, MODEM_SERIAL_RX_PIN, MODEM_SERIAL_TX_PIN);
    MODEM_SERIAL.flush();
    digitalWrite(BOARD_POWERON_PIN, HIGH);

    if (m_modem->testAT(200)) {
        m_modem->restart();
        delay(1000);
    }

    uint8_t at_retries = 0;
    while (!m_modem->testAT(200)) {
        INFO("...");
        delay(1000);
        if (++at_retries > 30) {
            ERROR("Modem not responding, rebooting");
            reset_modem();
            at_retries = 0;
        }
    }

    m_modem->init();
    uint8_t imei_retries = 0;
    bool imei_success = false;
    while (!imei_success) {
        String imei = m_modem->getIMEI();
        if (imei.toInt() != 0 && imei.length() > 5) {
            imei_success = true;
            imei.substring(8, 15).toCharArray(m_nodeId, 8);
        } else if (++imei_retries > 10) {
            ERROR("Failed to get IMEI, rebooting");
            reset_modem();
            imei_retries = 0;
        }
    }

    INFO_VALUE("Node ID: ", m_nodeId);

    m_ota_status = ota_status;

    uint8_t sim_status = m_modem->getSimStatus();
    if (sim_status == SIM_LOCKED) {
        if (strlen(GSM_PIN) == 0 || !m_modem->simUnlock(GSM_PIN)) {
            m_error = 2;
            ERROR("SIM-card locked!");
            return false;
        }
    } else if (sim_status == SIM_ERROR) {
        m_error = 1;
        ERROR("SIM-card missing!");
        return false;
    }

    m_modem->sendAT("+CNMP=2");
    m_modem->waitResponse(1000L);

    return true;
}

Communication::modem_state Communication::get_state()
{
    return m_modem_state;
}

void Communication::set_state(Communication::modem_state state)
{
    m_requested_modem_state = state;
}

bool Communication::modem_is_off()
{
    return m_modem_state == modem_state::off;
}

bool Communication::connected_to_server()
{
    return m_modem_state == modem_state::server_ready;
}

void Communication::turn_modem_off()
{
    disconnect_server();
    m_modem->poweroff();
    delay(500);
}

void Communication::turn_modem_on()
{
    if (!m_modem->testAT(500)) {
        digitalWrite(BOARD_POWERON_PIN, HIGH);
        digitalWrite(MODEM_POWER_PIN, LOW);
        delay(100);
        digitalWrite(MODEM_POWER_PIN, HIGH);
        delay(100);
        digitalWrite(MODEM_POWER_PIN, LOW);
        delay(3000);
    }
}

void Communication::reset_modem()
{
    digitalWrite(MODEM_RESET_PIN, HIGH);
    delay(500);
    digitalWrite(MODEM_RESET_PIN, LOW);
    delay(500);
    disconnect_server();
}

bool Communication::connect_server()
{
    m_server_ready = true;
    return true;
}

void Communication::disconnect_server()
{
    m_server_ready = false;
    m_client->stop();
}

bool Communication::send_location(location_update* l)
{
    if (!connected_to_server()) {
        return false;
    }

    char timestamp[24] = "";
    if (l->year > 2000) {
        snprintf(timestamp,
                 sizeof(timestamp),
                 "%04d-%02d-%02dT%02d:%02d:%02dZ",
                 l->year,
                 l->month,
                 l->day,
                 l->hour,
                 l->minute,
                 l->second);
    }

    char request_path[256];
    snprintf(request_path,
             sizeof(request_path),
             "%s?id=%s&lat=%.6f&lon=%.6f&speed=%.1f&bearing=%u&altitude=%.1f%s%s",
             TRACCAR_PATH,
             TRACCAR_DEVICE_ID,
             l->lat,
             l->lon,
             l->speed,
             l->course,
             l->alt,
             timestamp[0] ? "&timestamp=" : "",
             timestamp);

    return send_http_get(request_path);
}

bool Communication::send_status(uint8_t soc_in, bool charging)
{
    (void)soc_in;
    (void)charging;
    return connected_to_server();
}

bool Communication::send_ota_status(ota::status status)
{
    (void)status;
    return false;
}

bool Communication::request_settings()
{
    return false;
}

uint8_t Communication::get_signal_strength()
{
    return (m_modem->getSignalQuality() * 827 + 127) >> 8;
}

void Communication::update()
{
    if (util::get_time_diff(m_status_check_timestamp) > 30 * 1000
        || m_modem_state != m_requested_modem_state) {
        INFO("Net check!");
        m_last_modem_state = m_modem_state;

        if (m_server_ready && m_modem->isGprsConnected())
            m_modem_state = modem_state::server_ready;
        else if (!m_modem->testAT(200))
            m_modem_state = modem_state::off;
        else if (m_modem->isGprsConnected())
            m_modem_state = modem_state::active_data_connection;
        else if (m_modem->isNetworkConnected())
            m_modem_state = modem_state::registered_to_network;
        else if (m_modem->testAT(300))
            m_modem_state = modem_state::not_registered_to_network;

        if (m_modem_state != m_last_modem_state) {
            m_mode_change_timestamp = millis();
        }

        INFO_VALUE("Modem state: ", m_modem_state);
        INFO_VALUE("Target state: ", m_requested_modem_state);

        if (m_modem_state == modem_state::off) {
            if (m_requested_modem_state > m_modem_state) {
                INFO("Turning modem on");
                if (m_modem_failed_turn_on_counter < 5) {
                    turn_modem_on();
                    m_modem_failed_turn_on_counter++;
                } else {
                    reset_modem();
                    m_modem_failed_turn_on_counter = 0;
                }
            }
        } else if (m_modem_state == modem_state::not_registered_to_network) {
            if (util::get_time_diff(m_mode_change_timestamp) > 120 * 1000) {
                ERROR("Network registeration failed, rebooting modem!");
                reset_modem();
            }
            if (m_requested_modem_state == modem_state::off) {
                INFO("Turning modem off");
                turn_modem_off();
                m_modem_failed_turn_on_counter = 0;
            }
        } else if (m_modem_state == modem_state::registered_to_network) {
            if (m_requested_modem_state > m_modem_state) {
                INFO("Connecting to GPRS");
                delay(700);
                m_modem->gprsConnect(APN, GPRS_USER, GPRS_PASS);
            } else if (m_requested_modem_state == modem_state::off) {
                INFO("Turning modem off");
                turn_modem_off();
            }
        } else if (m_modem_state == modem_state::active_data_connection) {
            if (m_requested_modem_state > m_modem_state) {
                INFO("Preparing Traccar transport");
                connect_server();
            } else if (m_requested_modem_state < m_modem_state) {
                INFO("Disconnecting GPRS");
                disconnect_server();
                m_modem->gprsDisconnect();
            }
        } else if (m_modem_state == modem_state::server_ready) {
            if (m_requested_modem_state < m_modem_state) {
                INFO("Disconnecting Traccar transport");
                disconnect_server();
            }
        }

        m_status_check_timestamp = millis();
    }
}

bool Communication::send_http_get(const char* request_path)
{
    if (!m_client->connect(TRACCAR_HOST, TRACCAR_PORT)) {
        ERROR("Traccar TCP connect failed");
        m_server_ready = false;
        return false;
    }

    m_client->print("GET ");
    m_client->print(request_path);
    m_client->print(" HTTP/1.1\r\nHost: ");
    m_client->print(TRACCAR_HOST);
    m_client->print("\r\nUser-Agent: T-A7670E-Traccar/");
    m_client->print(VERSION);
    m_client->print("\r\nConnection: close\r\n\r\n");

    String status_line;
    uint32_t start = millis();
    while (util::get_time_diff(start) < 10000) {
        while (m_client->available()) {
            char c = m_client->read();
            if (c == '\r') {
                continue;
            }
            if (c == '\n') {
                bool ok = status_line.startsWith("HTTP/1.1 200") || status_line.startsWith("HTTP/1.0 200");
                m_client->stop();
                if (!ok) {
                    ERROR("Traccar HTTP request failed");
                    ERROR(status_line.c_str());
                }
                return ok;
            }
            status_line += c;
        }
        delay(10);
    }

    ERROR("Traccar HTTP timeout");
    m_client->stop();
    return false;
}

bool Communication::get_ota_wifi_details(wifi_details* ota_wifi)
{
    if (strlen(m_wifi_details.wifi_ssid) > 0 && strlen(m_wifi_details.wifi_passwd) > 0) {
        strcpy(ota_wifi->wifi_ssid, m_wifi_details.wifi_ssid);
        strcpy(ota_wifi->wifi_passwd, m_wifi_details.wifi_passwd);
        return true;
    }
    return false;
}
