# T-A7670E Tracker Client

Adattamento del progetto `eaxsi/sim7000-tracker` per la scheda LilyGO `T-A7670E`, con struttura compatibile con `PlatformIO`.

## Stato

- Base del progetto importata da `sim7000-tracker`
- Pinout e sequenza di power-on adattati a `T-A7670E`
- Build verificata con `PlatformIO`
- GNSS letto via comandi AT del modem `A7670`

## Requisiti

- Board: `LilyGO T-A7670E ESP32`
- Framework: Arduino
- Tooling: PlatformIO

## Build

```ini
pio run
```

## Upload

```ini
pio run -t upload
```

Se la scheda non entra automaticamente in flashing, usa il pulsante `IO0` durante il reset come da documentazione LilyGO.

## Configurazione

Modifica `config.h`:

```cpp
#define PROJECT_NAME "tracker"

#define BROKER_HOST ""
#define BROKER_PORT 1883
#define BROKER_USER ""
#define BROKER_PASSWD ""

#define GSM_PIN ""
#define APN "iot.1nce.net"
#define GPRS_USER ""
#define GPRS_PASS ""

#define HTTP_OTA_URL ""
```

## Pin usati

- `GPIO12`: alimentazione periferiche/modem, mantenuto alto
- `GPIO4`: `PWRKEY` modem
- `GPIO5`: reset modem
- `GPIO25`: `DTR`
- `GPIO26`: TX ESP32 verso modem
- `GPIO27`: RX ESP32 dal modem
- `GPIO35`: lettura batteria
- `GPIO0`: reed switch esterno
- `GPIO32`: sensore vibrazione esterno

## Note

- Il `T-A7670E` non offre un LED utente equivalente a quello del `T-SIM7000G`, quindi la UI luminosa del progetto viene disattivata.
- Questo adattamento assume un modem `A7670E` con GNSS integrato. Alcune varianti `A7670` non includono GPS interno.
- La build verificata usa `TinyGSM` ufficiale per rete/MQTT e comandi AT diretti per il GNSS.
