#include "gnss.h"

#include <math.h>

namespace {
bool extract_gnss_payload(const String& response, String& payload)
{
    int start = response.indexOf("+CGNSSINFO:");
    if (start < 0) {
        return false;
    }

    int line_end = response.indexOf('\n', start);
    if (line_end < 0) {
        line_end = response.length();
    }

    payload = response.substring(start + 11, line_end);
    payload.trim();
    return payload.length() > 0;
}

bool next_field(const String& payload, int& cursor, String& field)
{
    if (cursor > payload.length()) {
        return false;
    }

    int sep = payload.indexOf(',', cursor);
    if (sep < 0) {
        field = payload.substring(cursor);
        cursor = payload.length() + 1;
    } else {
        field = payload.substring(cursor, sep);
        cursor = sep + 1;
    }
    field.trim();
    return true;
}

float convert_nmea_coordinate(const String& raw, const String& hemisphere)
{
    if (raw.length() < 4) {
        return 0.0f;
    }

    float value = raw.toFloat();
    int degrees = static_cast<int>(value / 100.0f);
    float minutes = value - (degrees * 100.0f);
    float decimal = degrees + (minutes / 60.0f);

    if (hemisphere == "S" || hemisphere == "W") {
        decimal *= -1.0f;
    }
    return decimal;
}
}

Gnss::Gnss(TinyGsm* m)
{
    m_modem = m;
    m_state = state::off;
    m_requested_state = state::off;
}

void Gnss::turn_on()
{
    m_requested_state = state::fix;
}

void Gnss::turn_off()
{
    m_requested_state = state::off;
}

bool Gnss::is_on()
{
    return m_state != state::off;
}

bool Gnss::has_fix()
{
    return m_state == state::fix;
}

bool Gnss::has_initial_fix()
{
    return m_initial_fix_received;
}

bool Gnss::is_moving()
{
    return m_loc.speed >= m_moving_speed_threshold;
}

bool Gnss::get_location(location_update* loc)
{
    m_old_loc = m_loc;

    m_modem->sendAT("+CGNSSINFO");
    String response;
    if (m_modem->waitResponse(10000L, response) != 1) {
        return false;
    }

    String payload;
    if (!extract_gnss_payload(response, payload)) {
        return false;
    }

    int cursor = 0;
    String field;

    next_field(payload, cursor, field);
    uint8_t fix_mode = static_cast<uint8_t>(field.toInt());
    if (fix_mode < 1) {
        return false;
    }

    next_field(payload, cursor, field);
    m_loc.vsat = field.toInt();
    next_field(payload, cursor, field);
    next_field(payload, cursor, field);
    next_field(payload, cursor, field);

    String lat_raw;
    String lat_ns;
    String lon_raw;
    String lon_ew;
    next_field(payload, cursor, lat_raw);
    next_field(payload, cursor, lat_ns);
    next_field(payload, cursor, lon_raw);
    next_field(payload, cursor, lon_ew);

    next_field(payload, cursor, field);
    if (field.length() >= 6) {
        m_loc.day = field.substring(0, 2).toInt();
        m_loc.month = field.substring(2, 4).toInt();
        m_loc.year = 2000 + field.substring(4, 6).toInt();
    }

    next_field(payload, cursor, field);
    if (field.length() >= 6) {
        m_loc.hour = field.substring(0, 2).toInt();
        m_loc.minute = field.substring(2, 4).toInt();
        m_loc.second = field.substring(4, 6).toInt();
    }

    next_field(payload, cursor, field);
    m_loc.alt = field.toFloat();
    next_field(payload, cursor, field);
    m_loc.speed = field.toFloat() * 1.852f;
    next_field(payload, cursor, field);
    next_field(payload, cursor, field);
    m_loc.accuracy = field.toFloat();
    next_field(payload, cursor, field);
    next_field(payload, cursor, field);

    m_loc.lat = convert_nmea_coordinate(lat_raw, lat_ns);
    m_loc.lon = convert_nmea_coordinate(lon_raw, lon_ew);
    m_loc.usat = 0;

    bool fix = m_loc.lat != 0.0f && m_loc.lon != 0.0f;
    if (!fix) {
        return false;
    }

    loc->lat = m_loc.lat;
    loc->lon = m_loc.lon;
    loc->alt = m_loc.alt;
    loc->vsat = m_loc.vsat;
    loc->usat = m_loc.usat;
    loc->accuracy = m_loc.accuracy;
    loc->speed = max(m_loc.speed, 0.0f);

    bool time_not_changed = m_loc.year == m_old_loc.year && m_loc.month == m_old_loc.month
                            && m_loc.day == m_old_loc.day && m_loc.hour == m_old_loc.hour
                            && m_loc.minute == m_old_loc.minute && m_loc.second == m_old_loc.second;
    bool location_not_changed
        = m_loc.lat == m_old_loc.lat && m_loc.lon == m_old_loc.lon && m_loc.alt == m_old_loc.alt;

    loc->course = get_bearing(m_old_loc.lat, m_old_loc.lon, m_loc.lat, m_loc.lon);
    m_device_stuck = time_not_changed && location_not_changed;

    return fix;
}

bool Gnss::turn_on_impl()
{
    m_modem->sendAT("+CGNSSPWR=1");
    return m_modem->waitResponse(30000L) == 1;
}

bool Gnss::turn_off_impl()
{
    m_modem->sendAT("+CGNSSPWR=0");
    return m_modem->waitResponse(1000L) == 1;
}

bool Gnss::has_fix_impl()
{
    location_update loc;
    return get_location(&loc);
}

float Gnss::get_bearing(float lat, float lon, float lat2, float lon2)
{
    float teta1 = radians(lat);
    float teta2 = radians(lat2);
    float delta1 = radians(lat2 - lat);
    float delta2 = radians(lon2 - lon);

    float y = sin(delta2) * cos(teta2);
    float x = cos(teta1) * sin(teta2) - sin(teta1) * cos(teta2) * cos(delta2);
    float brng = atan2(y, x);
    brng = degrees(brng);
    brng = (((int)brng + 360) % 360);

    return brng;
}

void Gnss::update()
{
    switch (m_state) {
        case state::off: {
            if (m_requested_state > m_state) {
                turn_on_impl();
                m_state = state::no_fix;
            }
            break;
        }
        case state::no_fix: {
            if (m_requested_state < m_state) {
                //turn off
                turn_off_impl();
                m_state = state::off;
            } else if (has_fix_impl()) {
                m_state = state::fix;
                m_initial_fix_received = true;
            }
            break;
        }
        case state::fix: {
            if (m_requested_state < m_state) {
                // turn off
                turn_off_impl();
                m_state = state::off;
            } else {
                bool non_valid_data = m_loc.vsat > 10000 && m_loc.usat == 0;
                if (non_valid_data || m_device_stuck) {
                    turn_off_impl();
                    turn_on_impl();
                    m_state = state::no_fix;
                }
            }
            break;
        }
        default: break;
    }
}
