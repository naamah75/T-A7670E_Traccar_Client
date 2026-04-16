# T-A7670E Tracker Client

Adattamento del progetto `eaxsi/sim7000-tracker` per la scheda LilyGO `T-A7670E`, con struttura compatibile con `PlatformIO` e invio posizione verso Traccar via HTTP.

## Stato

- Base del progetto importata da `sim7000-tracker`
- Pinout e sequenza di power-on adattati a `T-A7670E`
- Trasporto MQTT rimosso
- Invio posizione via HTTP GET compatibile con Traccar/OsmAnd
- Build verificata con `PlatformIO`

## Requisiti

- Board: `LilyGO T-A7670E ESP32`
- Framework: Arduino
- Tooling: PlatformIO
- SIM con APN dati valido

## Build

```ini
pio run
```

## Upload

```ini
pio run -t upload
```

Se la scheda non entra automaticamente in flashing, usa il pulsante `IO0` durante il reset come da documentazione LilyGO.

## Configurazione locale

Il file reale `config.h` e' locale e non viene pushato.

1. Copia `config.example.h` in `config.h`
2. Personalizza i valori locali

Configurazione attuale richiesta:

```cpp
#pragma once

#define TRACCAR_HOST "185.58.121.235"
#define TRACCAR_PORT 30206
#define TRACCAR_PATH "/"
#define TRACCAR_DEVICE_ID "862771076817991"

#define GSM_PIN ""
#define APN "TM"
#define GPRS_USER ""
#define GPRS_PASS ""

#define HTTP_OTA_URL ""
```

## Protocollo Traccar

Il progetto usa richieste HTTP del tipo:

```text
GET /?id=<deviceId>&lat=<lat>&lon=<lon>&speed=<speed>&bearing=<bearing>&altitude=<altitude>&timestamp=<utc>
```

Questo segue l'approccio del protocollo HTTP/OsmAnd comunemente usato con Traccar.

## Limiti attuali

- Nessun controllo remoto via MQTT
- Nessuna sincronizzazione impostazioni dal server
- OTA ancora solo via Wi-Fi e URL esplicito

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
