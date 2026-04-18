/**
 * PlatformIO port of the official LilyGO Traccar example for T-A7670E.
 */

#define TINY_GSM_RX_BUFFER 1024
#define REPORT_LOCATION_RATE_SECOND 20

#include <Arduino.h>
#include <cstring>
#include <cstdio>

#include "utilities.h"
#include <TinyGsmClient.h>

#ifndef MODEM_DTR_PIN
#error "This board does not support modem sleep function"
#endif

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, Serial);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);

bool use_ipv6_access_point = USE_IPV6_ACCESS_POINT != 0;
String modemName = "UNKNOWN";
String apn = NETWORK_APN;
const char* client_id = TRACCAR_DEVICE_ID;
const char* request_url = TRACCAR_URL;
const char* post_format =
    "deviceid=%s&lat=%.7f&lon=%.7f&timestamp=%04d-%02d-%02dT%02d:%02d:%02dZ&speed=%.2f&bearing=%.2f&altitude=%.2f&hdop=%.2f&batt=%u";

void light_sleep_delay(uint32_t ms)
{
#ifdef DEBUG_SKETCH
    delay(ms);
#else
    esp_sleep_enable_timer_wakeup(ms * 1000ULL);
    esp_light_sleep_start();
#endif
}

void apply_fake_gps(GPSInfo& info)
{
    info.isFix = true;
    info.latitude = DEBUG_FAKE_LAT;
    info.longitude = DEBUG_FAKE_LON;
    info.speed = DEBUG_FAKE_SPEED;
    info.course = DEBUG_FAKE_COURSE;
    info.altitude = DEBUG_FAKE_ALTITUDE;
    info.HDOP = 99.0f;
    info.PDOP = 99.0f;
    info.VDOP = 99.0f;
    info.gps_satellite_num = 0;
    info.beidou_satellite_num = 0;
    info.glonass_satellite_num = 0;
    info.galileo_satellite_num = 0;
    info.year = 2026;
    info.month = 1;
    info.day = 1;
    info.hour = 0;
    info.minute = 0;
    info.second = 0;
    Serial.println("Using fake GPS position for debug");
}

void log_gps_info(const GPSInfo& info)
{
    Serial.println();
    Serial.print("FixMode:");
    Serial.println(info.isFix);
    Serial.print("Latitude:");
    Serial.println(info.latitude, 6);
    Serial.print("Longitude:");
    Serial.println(info.longitude, 6);
    Serial.print("Speed:");
    Serial.println(info.speed);
    Serial.print("Altitude:");
    Serial.println(info.altitude);
    Serial.println("Visible Satellites:");
    Serial.print(" GPS Satellites:");
    Serial.println(info.gps_satellite_num);
    Serial.print(" BEIDOU Satellites:");
    Serial.println(info.beidou_satellite_num);
    Serial.print(" GLONASS Satellites:");
    Serial.println(info.glonass_satellite_num);
    Serial.print(" GALILEO Satellites:");
    Serial.println(info.galileo_satellite_num);
    Serial.println("Date Time:");
    Serial.print("Year:");
    Serial.print(info.year);
    Serial.print(" Month:");
    Serial.print(info.month);
    Serial.print(" Day:");
    Serial.println(info.day);
    Serial.print("Hour:");
    Serial.print(info.hour);
    Serial.print(" Minute:");
    Serial.print(info.minute);
    Serial.print(" Second:");
    Serial.println(info.second);
    Serial.print("Course:");
    Serial.println(info.course);
    Serial.print("PDOP:");
    Serial.println(info.PDOP);
    Serial.print("HDOP:");
    Serial.println(info.HDOP);
    Serial.print("VDOP:");
    Serial.println(info.VDOP);
    Serial.print("GPS/GNSS Based Location String:");
    Serial.println(modem.getGPSraw());
}

bool post_location(const GPSInfo& info)
{
    char post_buffer[256];
    uint8_t battery_percent = 100;
    snprintf(post_buffer,
             sizeof(post_buffer),
             post_format,
             client_id,
             info.latitude,
             info.longitude,
             info.year,
             info.month,
             info.day,
             info.hour,
             info.minute,
             info.second,
             info.speed,
             info.course,
             info.altitude,
             info.HDOP,
             battery_percent);

    Serial.print("Request url:");
    Serial.println(request_url);
    Serial.print("Post body  :");
    Serial.println(post_buffer);

    if (!modem.https_begin()) {
        Serial.println("HTTP init failed");
        return false;
    }

    modem.https_set_timeout(30, 10, 20);
    modem.https_set_content_type("application/x-www-form-urlencoded");
    modem.https_set_user_agent("TinyGSM/LilyGo-A76XX");

    if (!modem.https_set_url(request_url)) {
        Serial.println("Failed to set URL");
        modem.https_end();
        return false;
    }

    int httpCode = modem.https_post(post_buffer);
    Serial.print("HTTP code  :");
    Serial.println(httpCode);
    modem.https_end();
    return httpCode == 200;
}

bool acquire_location(GPSInfo& info)
{
    bool ok = modem.getGPS_Ex(info);
    if (ok) {
        log_gps_info(info);
        return true;
    }

#if DEBUG_USE_FAKE_GPS
    apply_fake_gps(info);
    log_gps_info(info);
    return true;
#else
    return false;
#endif
}

void modem_enter_sleep(uint32_t ms)
{
#ifdef DEBUG_SKETCH
    Serial.printf("DEBUG_SKETCH active, skipping modem sleep for %u seconds\n", ms / 1000);
    delay(ms);
#else
    Serial.printf("Enter modem sleep mode,Will wake up in %u seconds\n", ms / 1000);
    pinMode(MODEM_DTR_PIN, OUTPUT);
    digitalWrite(MODEM_DTR_PIN, HIGH);
    if (!modem.sleepEnable(true)) {
        Serial.println("modem sleep failed!");
    } else {
        Serial.println("Modem enter sleep mode success!");
    }
    light_sleep_delay(ms);
    digitalWrite(MODEM_DTR_PIN, LOW);
    light_sleep_delay(500);
#endif
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Start Official Traccar Baseline");

    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);

#ifdef BOARD_POWERON_PIN
    pinMode(BOARD_POWERON_PIN, OUTPUT);
    digitalWrite(BOARD_POWERON_PIN, HIGH);
    gpio_hold_en((gpio_num_t)BOARD_POWERON_PIN);
    gpio_deep_sleep_hold_en();
#endif

#ifdef MODEM_RESET_PIN
    pinMode(MODEM_RESET_PIN, OUTPUT);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);
    delay(100);
    digitalWrite(MODEM_RESET_PIN, MODEM_RESET_LEVEL);
    delay(2600);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);
    gpio_hold_en((gpio_num_t)MODEM_RESET_PIN);
    gpio_deep_sleep_hold_en();
#endif

    pinMode(MODEM_DTR_PIN, OUTPUT);
    digitalWrite(MODEM_DTR_PIN, LOW);

    pinMode(BOARD_PWRKEY_PIN, OUTPUT);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_PWRKEY_PIN, HIGH);
    delay(MODEM_POWERON_PULSE_WIDTH_MS);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);

    Serial.println("Start modem...");
    int retry = 0;
    while (!modem.testAT(1000)) {
        Serial.println(".");
        if (retry++ > 30) {
            digitalWrite(BOARD_PWRKEY_PIN, LOW);
            delay(100);
            digitalWrite(BOARD_PWRKEY_PIN, HIGH);
            delay(MODEM_POWERON_PULSE_WIDTH_MS);
            digitalWrite(BOARD_PWRKEY_PIN, LOW);
            retry = 0;
        }
    }
    Serial.println();

    while (1) {
        modemName = modem.getModemName();
        if (modemName == "UNKNOWN") {
            Serial.println("Unable to obtain module information normally, try again");
            delay(1000);
        } else {
            Serial.print("Model Name:");
            Serial.println(modemName);
            break;
        }
    }

    SimStatus sim = SIM_ERROR;
    while (sim != SIM_READY) {
        sim = modem.getSimStatus();
        switch (sim) {
            case SIM_READY:
                Serial.println("SIM card online");
                break;
            case SIM_LOCKED:
                if (strlen(GSM_PIN) > 0) {
                    modem.simUnlock(GSM_PIN);
                    Serial.println("Unlocking SIM card");
                } else {
                    Serial.println("SIM card locked and no GSM_PIN configured");
                }
                break;
            default:
                break;
        }
        light_sleep_delay(1000);
    }

#ifdef TINY_GSM_MODEM_HAS_NETWORK_MODE
    if (!modem.setNetworkMode(MODEM_NETWORK_AUTO)) {
        Serial.println("Set network mode failed!");
    }
    Serial.print("Current network mode : ");
    Serial.println(modem.getNetworkModeString());
#endif

#ifdef TINY_GSM_MODEM_HAS_PREFERRED_MODE
    if (!modem.setPreferredMode(MODEM_PREFERRED_CATM_NBIOT)) {
        Serial.println("Set network preferred failed!");
    }
    Serial.print("Current preferred mode : ");
    Serial.println(modem.getPreferredModeString());
#endif

    Serial.printf("Set network apn : %s\n", NETWORK_APN);
    if (!modem.setNetworkAPN(NETWORK_APN)) {
        Serial.println("Set network apn error !");
    }

    int16_t sq;
    Serial.print("Wait for the modem to register with the network.");
    RegStatus status = REG_NO_RESULT;
    while (status == REG_NO_RESULT || status == REG_SEARCHING || status == REG_UNREGISTERED) {
        status = modem.getRegistrationStatus();
        switch (status) {
            case REG_UNREGISTERED:
            case REG_SEARCHING:
                sq = modem.getSignalQuality();
                Serial.printf("[%lu] Signal Quality:%d\n", millis() / 1000, sq);
                light_sleep_delay(1000);
                break;
            case REG_DENIED:
                Serial.println("Network registration was rejected, please check if the APN is correct");
                return;
            case REG_OK_HOME:
                Serial.println("Online registration successful");
                break;
            case REG_OK_ROAMING:
                Serial.println("Network registration successful, roaming");
                break;
            default:
                Serial.printf("Registration Status:%d\n", status);
                light_sleep_delay(1000);
                break;
        }
    }

#ifdef MODEM_REG_SMS_ONLY
    while (status == REG_SMS_ONLY) {
        Serial.println("Registered for SMS only; data not available on this registration");
        delay(5000);
    }
#endif

    String ueInfo;
    if (modem.getSystemInformation(ueInfo)) {
        Serial.print("Inquiring UE system information:");
        Serial.println(ueInfo);
    }

    Serial.print("Connecting to network with APN:");
    Serial.println(apn);
    Serial.print("Use IPv6 access point:");
    Serial.println(use_ipv6_access_point ? "true" : "false");
    retry = 3;
    while (retry--) {
        if (modem.setNetworkActive(apn, use_ipv6_access_point)) {
            break;
        }
        Serial.println("Enable network failed, retry after 3s...");
        delay(3000);
    }
    if (retry < 0) {
        Serial.println("Failed to enable network!");
        return;
    }

    light_sleep_delay(5000);
    Serial.print("Network IP:");
    Serial.println(modem.getLocalIP());

    Serial.println("Enabling GPS/GNSS/GLONASS");
    while (!modem.enableGPS(MODEM_GPS_ENABLE_GPIO, MODEM_GPS_ENABLE_LEVEL)) {
        Serial.print(".");
        light_sleep_delay(500);
    }
    Serial.println();
    Serial.println("GPS Enabled");

    modem.setGPSBaud(115200);

#if defined(TINY_GSM_MODEM_A7670) || defined(TINY_GSM_MODEM_A7608)
    modem.setGPSMode(GNSS_MODE_GPS_BDS_GALILEO_SBAS_QZSS);
#endif

#ifndef TINY_GSM_MODEM_SIM7670G
    Serial.print("GPS acceleration is enable");
    if (!modem.enableAGPS()) {
        Serial.println(" failed !!!");
    } else {
        Serial.println(" success!!!");
    }
#endif
}

void loop()
{
    GPSInfo info;

    if (!modem.testAT(3000)) {
        Serial.println("Power Off , restart device");
        Serial.flush();
        delay(100);
        esp_restart();
    }

    bool has_location = acquire_location(info);
    if (!has_location) {
        Serial.println("No valid GPS position yet, retry later");
        light_sleep_delay(15000);
        return;
    }

    Serial.println("GPS position ready, sending to Traccar...");
    if (post_location(info)) {
        Serial.println("Traccar upload success");
        modem_enter_sleep(REPORT_LOCATION_RATE_SECOND * 1000);
    } else {
        Serial.println("Traccar upload failed");
        light_sleep_delay(REPORT_LOCATION_RATE_SECOND * 1000);
    }
}
