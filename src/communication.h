#pragma once

#include "Arduino.h"

#include "hardware_configuration.h"

#include <TinyGsmClient.h>

#include "app_config.h"
#include "../version.h"
#include "common.h"
#include "log.h"
#include "settings.h"
#include "ota.h"

#define TINY_GSM_USE_GPRS true

class Communication
{
    public:
        enum modem_state {
            off,
            sim_locked,
            sim_unlocked,
            not_registered_to_network,
            registered_to_network,
            active_data_connection,
            server_ready
        };

        Communication(TinyGsm* modem, TinyGsmClient* client, Settings* config);
        bool init(ota::status);
        void update();

        void set_state(modem_state);
        modem_state get_state();
        bool connected_to_server();
        bool modem_is_off();
        bool send_location(location_update* loc);
        bool send_status(uint8_t soc, bool charging);
        bool request_settings();
        bool get_ota_wifi_details(wifi_details* ota_wifi);
        bool send_ota_status(ota::status status);
        void reset_modem();

    private:
        bool connect_server();
        void disconnect_server();
        void turn_modem_off();
        void turn_modem_on();
        bool send_http_get(const char* request_path);
        uint8_t get_signal_strength();

        modem_state m_modem_state = modem_state::off;
        modem_state m_last_modem_state = modem_state::off;
        modem_state m_requested_modem_state = modem_state::off;

        Settings* m_config;

        uint8_t m_error = 0;
        ota::status m_ota_status = ota::status::none;
        char m_nodeId[8] = "";

        uint32_t m_status_check_timestamp = 0;
        uint32_t m_mode_change_timestamp = 0;
        wifi_details m_wifi_details = {};
        bool m_server_ready = false;
        uint8_t m_modem_failed_turn_on_counter = 0;

        TinyGsm* m_modem;
        TinyGsmClient* m_client;
};
