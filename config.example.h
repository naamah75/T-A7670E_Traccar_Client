#pragma once

#define TRACCAR_DEVICE_ID "862771076817991"
#define TRACCAR_URL "http://185.58.121.235:30206/"

#define NETWORK_APN "TM"
#define GSM_PIN ""

// Set to 1 only if your operator requires an IPv6 PDP context.
#define USE_IPV6_ACCESS_POINT 0

// Keep enabled while bringing up the official LilyGO baseline.
#define DEBUG_SKETCH 1
// Uncomment to dump all AT commands from TinyGSM.
// #define DUMP_AT_COMMANDS 1

// Debug-only fallback when GPS has no fix.
#define DEBUG_USE_FAKE_GPS 0
#define DEBUG_FAKE_LAT 45.464200
#define DEBUG_FAKE_LON 9.190000
#define DEBUG_FAKE_SPEED 0.0
#define DEBUG_FAKE_COURSE 0.0
#define DEBUG_FAKE_ALTITUDE 120.0
