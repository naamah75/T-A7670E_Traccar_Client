<p align="center">
  <img src="docs/logo.png" alt="T-A7670E Traccar Client" width="220">
</p>

<p align="center"><strong>Traccar client for LilyGO boards with PlatformIO</strong></p>

# T-A7670E Traccar Client

`PlatformIO` version based on the official LilyGO `examples/Traccar` example.

This repository started as a `T-A7670E` project, but it also includes `PlatformIO` environments for multiple LilyGO board variants supported by the same upstream example.

## Project Base

- reference source: `Xinyuan-LilyGO/LilyGo-Modem-Series/examples/Traccar`
- primary target board: `LilyGO T-A7670E`
- framework: Arduino with PlatformIO
- primary modem target: `A7670E`

## Supported Boards

- `LilyGO T-A7670E`
- `LilyGO T-Call A7670 V1.0`
- `LilyGO T-Call A7670 V1.1`
- `LilyGO T-SIM7670G-S3`
- `LilyGO T-A7608X`
- `LilyGO T-A7608X-S3`
- `LilyGO SIM7000G`
- `LilyGO SIM7070G`
- `LilyGO SIM7600X`
- `LilyGO SIM7000G-S3 Standard`
- `LilyGO SIM7080G-S3 Standard`
- `LilyGO SIM7670G-S3 Standard`
- `LilyGO A7670X-S3 Standard`
- `LilyGO SIM7600X-S3 Standard`
- `LilyGO T-SIM7080G-S3`
- `LilyGO T-Relay S3 SimShield`
- `LilyGO T-PCIE` variants
- `LilyGO T-ETH Elite` variants
- `LilyGO T-Internet-COM` variants

## Structure

- `src/main.cpp`: PlatformIO port of the official Traccar example
- `src/utilities.h`: LilyGO board pin and modem selection macros
- `config.h`: local untracked configuration
- `config.example.h`: public configuration template

## Local Configuration

`config.h` stays local and is not pushed.

Current template:

```cpp
#pragma once

#define TRACCAR_DEVICE_ID "your-device-id"
#define TRACCAR_URL "http://your-traccar-host:port/"

#define NETWORK_APN "your-apn"
#define GSM_PIN ""

#define USE_IPV6_ACCESS_POINT 0
#define DEBUG_SKETCH 1
// #define DUMP_AT_COMMANDS 1
```

## Build

```bash
pio run
```

To select a board environment other than the default one:

```bash
pio run -e t-a7670e
pio run -e t-call-a7670-v1-0
pio run -e sim7000g
```

The `PlatformIO` environments cover the main board-specific defines from the original LilyGO example.

## Upload

```bash
pio run -t upload
```

## Serial Monitor

```bash
pio device monitor -b 115200
```

## Notes

- the current base is the official LilyGO example, not `sim7000-tracker`
- Traccar transport uses plain `HTTP` against the server configured in `config.h`
- GNSS handling uses the LilyGO `TinyGSM` fork required by the upstream example
