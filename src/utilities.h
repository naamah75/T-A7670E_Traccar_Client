#pragma once

// PlatformIO port of the official LilyGO board-selection utilities.

#include "app_config.h"

// ESP32 boards
// #define LILYGO_T_A7670
// #define LILYGO_T_CALL_A7670_V1_0
// #define LILYGO_T_CALL_A7670_V1_1
// #define LILYGO_T_A7608X
// #define LILYGO_SIM7000G
// #define LILYGO_SIM7070G
// #define LILYGO_SIM7600X
// #define LILYGO_T_PCIE_A767X
// #define LILYGO_T_PCIE_SIM7000G
// #define LILYGO_T_PCIE_SIM7080G
// #define LILYGO_T_PCIE_SIM7600X
// #define LILYGO_T_PCIE_SIM7670G

// ESP32-S3 boards
// #define LILYGO_T_SIM7670G_S3
// #define LILYGO_T_A7608X_S3
// #define LILYGO_SIM7000G_S3_STAN
// #define LILYGO_SIM7080G_S3_STAN
// #define LILYGO_SIM7670G_S3_STAN
// #define LILYGO_A7670X_S3_STAN
// #define LILYGO_SIM7600X_S3_STAN
// #define LILYGO_SIM7080G_S3
// #define LILYGO_T_RELAY_S3_SIMSHIELD

// ESP32-S3 / product-family boards
// #define LILYGO_T_ETH_ELITE_A7670X
// #define LILYGO_T_ETH_ELITE_SIM7000X
// #define LILYGO_T_ETH_ELITE_SIM7080G
// #define LILYGO_T_ETH_ELITE_SIM7600X
// #define LILYGO_T_ETH_ELITE_SIM7670G
// #define LILYGO_T_INTERNET_COM_A7670X
// #define LILYGO_T_INTERNET_COM_SIM7000X
// #define LILYGO_T_INTERNET_COM_SIM7080G
// #define LILYGO_T_INTERNET_COM_SIM7600X
// #define LILYGO_T_INTERNET_COM_SIM7670G

#if defined(LILYGO_T_A7670)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (25)
    #define MODEM_TX_PIN                        (26)
    #define MODEM_RX_PIN                        (27)
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_POWERON_PIN                   (12)
    #define MODEM_RING_PIN                      (33)
    #define MODEM_RESET_PIN                     (5)
    #define BOARD_MISO_PIN                      (2)
    #define BOARD_MOSI_PIN                      (15)
    #define BOARD_SCK_PIN                       (14)
    #define BOARD_SD_CS_PIN                     (13)
    #define BOARD_BAT_ADC_PIN                   (35)
    #define MODEM_RESET_LEVEL                   HIGH
    #define SerialAT                            Serial1
    #define MODEM_GPS_ENABLE_GPIO               (-1)
    #define MODEM_GPS_ENABLE_LEVEL              (-1)
    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif
    #define PRODUCT_MODEL_NAME                  "LilyGo-A7670 ESP32 Version"

#elif defined(LILYGO_T_CALL_A7670_V1_0)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (14)
    #define MODEM_TX_PIN                        (26)
    #define MODEM_RX_PIN                        (25)
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_LED_PIN                       (12)
    #define LED_ON                              HIGH
    #define MODEM_RING_PIN                      (13)
    #define MODEM_RESET_PIN                     (27)
    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1
    #define MODEM_GPS_ENABLE_GPIO               (-1)
    #define MODEM_GPS_ENABLE_LEVEL              (-1)
    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif
    #define PRODUCT_MODEL_NAME                  "LilyGo-T-Call A7670 V1.0"

#elif defined(LILYGO_T_CALL_A7670_V1_1)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (32)
    #define MODEM_TX_PIN                        (27)
    #define MODEM_RX_PIN                        (26)
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_LED_PIN                       (13)
    #define LED_ON                              HIGH
    #define MODEM_RING_PIN                      (33)
    #define MODEM_RESET_PIN                     (5)
    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1
    #define MODEM_GPS_ENABLE_GPIO               (-1)
    #define MODEM_GPS_ENABLE_LEVEL              (-1)
    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif
    #define PRODUCT_MODEL_NAME                  "LilyGo-T-Call A7670 V1.1"

#elif defined(LILYGO_T_SIM7670G_S3)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (9)
    #define MODEM_TX_PIN                        (11)
    #define MODEM_RX_PIN                        (10)
    #define BOARD_PWRKEY_PIN                    (18)
    #define BOARD_LED_PIN                       (12)
    #define LED_ON                              (LOW)
    #define MODEM_RING_PIN                      (3)
    #define MODEM_RESET_PIN                     (17)
    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1
    #define BOARD_BAT_ADC_PIN                   (4)
    #define BOARD_SOLAR_ADC_PIN                 (5)
    #define BOARD_MISO_PIN                      (47)
    #define BOARD_MOSI_PIN                      (14)
    #define BOARD_SCK_PIN                       (21)
    #define BOARD_SD_CS_PIN                     (13)
    #ifndef TINY_GSM_MODEM_SIM7670G
        #define TINY_GSM_MODEM_SIM7670G
    #endif
    #define MODEM_GPS_ENABLE_GPIO               (4)
    #define MODEM_GPS_ENABLE_LEVEL              (1)
    #define PRODUCT_MODEL_NAME                  "LilyGo-SIM7670G-S3"

#elif defined(LILYGO_T_A7608X)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (25)
    #define MODEM_TX_PIN                        (26)
    #define MODEM_RX_PIN                        (27)
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_BAT_ADC_PIN                   (35)
    #define BOARD_POWERON_PIN                   (12)
    #define MODEM_RING_PIN                      (33)
    #define MODEM_RESET_PIN                     (5)
    #define BOARD_MISO_PIN                      (2)
    #define BOARD_MOSI_PIN                      (15)
    #define BOARD_SCK_PIN                       (14)
    #define BOARD_SD_CS_PIN                     (13)
    #define MODEM_RESET_LEVEL                   HIGH
    #define SerialAT                            Serial1
    #ifndef TINY_GSM_MODEM_A7608
        #define TINY_GSM_MODEM_A7608
    #endif
    #define MODEM_GPS_ENABLE_GPIO               (127)
    #define MODEM_GPS_ENABLE_LEVEL              (1)
    #define PRODUCT_MODEL_NAME                  "LilyGo-A7608X ESP32 Version"

#elif defined(LILYGO_T_A7608X_S3)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (7)
    #define MODEM_TX_PIN                        (17)
    #define MODEM_RX_PIN                        (18)
    #define BOARD_PWRKEY_PIN                    (15)
    #define BOARD_BAT_ADC_PIN                   (4)
    #define MODEM_RING_PIN                      (6)
    #define MODEM_RESET_PIN                     (16)
    #define BOARD_MISO_PIN                      (47)
    #define BOARD_MOSI_PIN                      (14)
    #define BOARD_SCK_PIN                       (21)
    #define BOARD_SD_CS_PIN                     (13)
    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1
    #ifndef TINY_GSM_MODEM_A7608
        #define TINY_GSM_MODEM_A7608
    #endif
    #define MODEM_GPS_ENABLE_GPIO               (127)
    #define MODEM_GPS_ENABLE_LEVEL              (1)
    #define PRODUCT_MODEL_NAME                  "LilyGo-A7608X-S3"

#elif defined(LILYGO_SIM7000G) || defined(LILYGO_SIM7070G)

    #define MODEM_DTR_PIN                       (25)
    #define MODEM_RX_PIN                        (26)
    #define MODEM_TX_PIN                        (27)
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_LED_PIN                       (12)
    #define LED_ON                              (LOW)
    #define BOARD_MISO_PIN                      (2)
    #define BOARD_MOSI_PIN                      (15)
    #define BOARD_SCK_PIN                       (14)
    #define BOARD_SD_CS_PIN                     (13)
    #define BOARD_BAT_ADC_PIN                   (35)
    #define BOARD_SOLAR_ADC_PIN                 (36)
    #define SerialAT                            Serial1
    #ifdef LILYGO_SIM7000G
      #ifndef TINY_GSM_MODEM_SIM7000SSL
        #define TINY_GSM_MODEM_SIM7000SSL
      #endif
      #define PRODUCT_MODEL_NAME                "LilyGo-SIM7000G ESP32 Version"
      #define MODEM_GPS_ENABLE_GPIO             (48)
    #endif
    #ifdef LILYGO_SIM7070G
      #ifndef TINY_GSM_MODEM_SIM7080
        #define TINY_GSM_MODEM_SIM7080
      #endif
      #define PRODUCT_MODEL_NAME                "LilyGo-SIM7070G ESP32 Version"
      #define MODEM_GPS_ENABLE_GPIO             (5)
    #endif
    #define MODEM_GPS_ENABLE_LEVEL              (1)

#elif defined(LILYGO_SIM7600X)

    #define MODEM_DTR_PIN                       (32)
    #define MODEM_RX_PIN                        (26)
    #define MODEM_TX_PIN                        (27)
    #define MODEM_FLIGHT_PIN                    (25)
    #define MODEM_STATUS_PIN                    (34)
    #define MODEM_RING_PIN                      (33)
    #define BOARD_MISO_PIN                      (2)
    #define BOARD_MOSI_PIN                      (15)
    #define BOARD_SCK_PIN                       (14)
    #define BOARD_SD_CS_PIN                     (13)
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_LED_PIN                       (12)
    #define LED_ON                              (HIGH)
    #define BOARD_BAT_ADC_PIN                   (35)
    #define BOARD_SOLAR_ADC_PIN                 (36)
    #define SerialAT                            Serial1
    #ifndef TINY_GSM_MODEM_SIM7600
      #define TINY_GSM_MODEM_SIM7600
    #endif
    #define MODEM_GPS_ENABLE_GPIO               (127)
    #define MODEM_GPS_ENABLE_LEVEL              (1)
    #define PRODUCT_MODEL_NAME                  "LilyGo-SIM7600X ESP32 Version"

#elif defined(LILYGO_SIM7000G_S3_STAN) || defined(LILYGO_SIM7080G_S3_STAN) || defined(LILYGO_SIM7670G_S3_STAN) || defined(LILYGO_A7670X_S3_STAN) || defined(LILYGO_SIM7600X_S3_STAN)

    #define MODEM_BAUDRATE                      (115200)
    #define BOARD_SDA_PIN                       (3)
    #define BOARD_SCL_PIN                       (2)
    #define MODEM_DTR_PIN                       (7)
    #define MODEM_TX_PIN                        (4)
    #define MODEM_RX_PIN                        (5)
    #define MODEM_RING_PIN                      (6)
    #define MODEM_GPS_RX_PIN                    (48)
    #define MODEM_GPS_TX_PIN                    (45)
    #define MODEM_GPS_PPS_PIN                   (17)
    #define GPS_SHIELD_WAKEUP_PIN               (0)
    #define BOARD_PWRKEY_PIN                    (46)
    #define BOARD_BAT_ADC_PIN                   (8)
    #define BOARD_SOLAR_ADC_PIN                 (18)
    #define BOARD_MISO_PIN                      (13)
    #define BOARD_MOSI_PIN                      (11)
    #define BOARD_SCK_PIN                       (12)
    #define BOARD_SD_CS_PIN                     (10)
    #define BOARD_POWER_SAVE_MODE_PIN           (42)
    #define SerialAT                            Serial1
    #ifdef LILYGO_SIM7000G_S3_STAN
      #ifndef TINY_GSM_MODEM_SIM7000SSL
        #define TINY_GSM_MODEM_SIM7000SSL
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (48)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-SIM7000G-S3-Standard"
    #elif defined(LILYGO_SIM7080G_S3_STAN)
      #ifndef TINY_GSM_MODEM_SIM7080
        #define TINY_GSM_MODEM_SIM7080
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (5)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-SIM7080G-S3-Standard"
    #elif defined(LILYGO_SIM7670G_S3_STAN)
      #ifndef TINY_GSM_MODEM_SIM7670G
        #define TINY_GSM_MODEM_SIM7670G
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (1)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-SIM7670G-S3-Standard"
    #elif defined(LILYGO_A7670X_S3_STAN)
      #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (1)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define MODEM_AUDIO_PA_ENABLE_GPIO        (3)
      #define MODEM_AUDIO_PA_ENABLE_LEVEL       (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-A7670X-S3-Standard"
    #else
      #ifndef TINY_GSM_MODEM_SIM7600
        #define TINY_GSM_MODEM_SIM7600
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (127)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define MODEM_AUDIO_PA_ENABLE_GPIO        (77)
      #define MODEM_AUDIO_PA_ENABLE_LEVEL       (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-SIM7600X-S3-Standard"
    #endif

#elif defined(LILYGO_SIM7080G_S3)

    #define SerialAT                            Serial1
    #define MODEM_BAUDRATE                      (115200)
    #define BOARD_PWRKEY_PIN                    (41)
    #define MODEM_DTR_PIN                       (42)
    #define MODEM_RING_PIN                      (3)
    #define MODEM_RX_PIN                        (4)
    #define MODEM_TX_PIN                        (5)
    #ifndef TINY_GSM_MODEM_SIM7080
      #define TINY_GSM_MODEM_SIM7080
    #endif
    #define PRODUCT_MODEL_NAME                  "LilyGo-T-SIM7080G-S3-PMU"

#elif defined(LILYGO_T_RELAY_S3_SIMSHIELD)

    #ifndef TINY_GSM_MODEM_A7670
      #define TINY_GSM_MODEM_A7670
    #endif
    #define BOARD_PWRKEY_PIN                    (46)
    #define MODEM_RX_PIN                        (9)
    #define MODEM_TX_PIN                        (3)
    #define MODEM_DTR_PIN                       (11)
    #define MODEM_RING_PIN                      (13)
    #define SerialAT                            Serial1
    #define PRODUCT_MODEL_NAME                  "LilyGo-T-RelayShield"

#elif defined(LILYGO_T_PCIE_A767X) || defined(LILYGO_T_PCIE_SIM7000G) || defined(LILYGO_T_PCIE_SIM7080G) || defined(LILYGO_T_PCIE_SIM7600X) || defined(LILYGO_T_PCIE_SIM7670G)

    #define LILYGO_T_PCIE
    #if defined(LILYGO_T_PCIE_A767X)
      #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (4)
      #define MODEM_GPS_ENABLE_LEVEL            (0)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-PCIE-A7670X"
    #elif defined(LILYGO_T_PCIE_SIM7000G)
      #ifndef TINY_GSM_MODEM_SIM7000SSL
        #define TINY_GSM_MODEM_SIM7000SSL
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (48)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-PCIE-SIM7000G"
    #elif defined(LILYGO_T_PCIE_SIM7080G)
      #ifndef TINY_GSM_MODEM_SIM7080
        #define TINY_GSM_MODEM_SIM7080
      #endif
      #define PRODUCT_MODEL_NAME                "LilyGo-T-PCIE-SIM7080G"
    #elif defined(LILYGO_T_PCIE_SIM7600X)
      #ifndef TINY_GSM_MODEM_SIM7600
        #define TINY_GSM_MODEM_SIM7600
      #endif
      #define PRODUCT_MODEL_NAME                "LilyGo-T-PCIE-SIM7600X"
    #else
      #ifndef TINY_GSM_MODEM_SIM7670G
        #define TINY_GSM_MODEM_SIM7670G
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (4)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-PCIE-SIM7670G"
    #endif

#elif defined(LILYGO_T_ETH_ELITE_A7670X) || defined(LILYGO_T_ETH_ELITE_SIM7000X) || defined(LILYGO_T_ETH_ELITE_SIM7080G) || defined(LILYGO_T_ETH_ELITE_SIM7600X) || defined(LILYGO_T_ETH_ELITE_SIM7670G)

    #define LILYGO_T_ETH_ELITE
    #if defined(LILYGO_T_ETH_ELITE_A7670X)
      #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (4)
      #define MODEM_GPS_ENABLE_LEVEL            (0)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-ETH-Elite-A7670X"
    #elif defined(LILYGO_T_ETH_ELITE_SIM7000X)
      #ifndef TINY_GSM_MODEM_SIM7000SSL
        #define TINY_GSM_MODEM_SIM7000SSL
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (48)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-ETH-Elite-SIM7000G"
    #elif defined(LILYGO_T_ETH_ELITE_SIM7080G)
      #ifndef TINY_GSM_MODEM_SIM7080
        #define TINY_GSM_MODEM_SIM7080
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (5)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-ETH-Elite-SIM7080G"
    #elif defined(LILYGO_T_ETH_ELITE_SIM7600X)
      #ifndef TINY_GSM_MODEM_SIM7600
        #define TINY_GSM_MODEM_SIM7600
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (127)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-ETH-Elite-SIM7600X"
    #else
      #ifndef TINY_GSM_MODEM_SIM7670G
        #define TINY_GSM_MODEM_SIM7670G
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (4)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-ETH-Elite-SIM7670G"
    #endif

#elif defined(LILYGO_T_INTERNET_COM_A7670X) || defined(LILYGO_T_INTERNET_COM_SIM7000X) || defined(LILYGO_T_INTERNET_COM_SIM7080G) || defined(LILYGO_T_INTERNET_COM_SIM7600X) || defined(LILYGO_T_INTERNET_COM_SIM7670G)

    #define LILYGO_T_INTERNET_COM
    #if defined(LILYGO_T_INTERNET_COM_A7670X)
      #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (4)
      #define MODEM_GPS_ENABLE_LEVEL            (0)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-Internet-COM--A7670X"
    #elif defined(LILYGO_T_INTERNET_COM_SIM7000X)
      #ifndef TINY_GSM_MODEM_SIM7000SSL
        #define TINY_GSM_MODEM_SIM7000SSL
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (48)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-Internet-COM--SIM7000G"
    #elif defined(LILYGO_T_INTERNET_COM_SIM7080G)
      #ifndef TINY_GSM_MODEM_SIM7080
        #define TINY_GSM_MODEM_SIM7080
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (5)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-Internet-COM--SIM7080G"
    #elif defined(LILYGO_T_INTERNET_COM_SIM7600X)
      #ifndef TINY_GSM_MODEM_SIM7600
        #define TINY_GSM_MODEM_SIM7600
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (127)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-Internet-COM--SIM7600X"
    #else
      #ifndef TINY_GSM_MODEM_SIM7670G
        #define TINY_GSM_MODEM_SIM7670G
      #endif
      #define MODEM_GPS_ENABLE_GPIO             (4)
      #define MODEM_GPS_ENABLE_LEVEL            (1)
      #define PRODUCT_MODEL_NAME                "LilyGo-T-Internet-COM--SIM7670G"
    #endif

#else
    #error "Select a LilyGO board macro through PlatformIO build flags"
#endif

#ifdef LILYGO_T_INTERNET_COM
    #define MODEM_RX_PIN                        (35)
    #define MODEM_TX_PIN                        (33)
    #define MODEM_RESET_PIN                     (32)
    #define BOARD_PWRKEY_PIN                    (32)
    #define BOARD_MISO_PIN                      (2)
    #define BOARD_MOSI_PIN                      (15)
    #define BOARD_SCK_PIN                       (14)
    #define BOARD_SD_CS_PIN                     (13)
    #define SerialAT                            Serial1
    #define MODEM_RESET_LEVEL                   HIGH
#endif

#ifdef LILYGO_T_PCIE
    #define MODEM_DTR_PIN                       (32)
    #define MODEM_RX_PIN                        (26)
    #define MODEM_TX_PIN                        (27)
    #define BOARD_POWERON_PIN                   (25)
    #define BOARD_PWRKEY_PIN                    (4)
    #define MODEM_RING_PIN                      (33)
    #define BOARD_LED_PIN                       (12)
    #define PMU_IRQ                             (35)
    #define LED_ON                              (LOW)
    #define SerialAT                            Serial1
    #ifndef MODEM_GPS_ENABLE_GPIO
      #define MODEM_GPS_ENABLE_GPIO             (-1)
    #endif
    #ifndef MODEM_GPS_ENABLE_LEVEL
      #define MODEM_GPS_ENABLE_LEVEL            (-1)
    #endif
#endif

#ifdef LILYGO_T_ETH_ELITE
    #define ETH_MISO_PIN                        (47)
    #define ETH_MOSI_PIN                        (21)
    #define ETH_SCLK_PIN                        (48)
    #define ETH_CS_PIN                          (45)
    #define ETH_INT_PIN                         (14)
    #define ETH_RST_PIN                         (-1)
    #define ETH_ADDR                            (1)
    #define SPI_MISO_PIN                        (9)
    #define SPI_MOSI_PIN                        (11)
    #define SPI_SCLK_PIN                        (10)
    #define SD_MISO_PIN                         (SPI_MISO_PIN)
    #define SD_MOSI_PIN                         (SPI_MOSI_PIN)
    #define SD_SCLK_PIN                         (SPI_SCLK_PIN)
    #define SD_CS_PIN                           (12)
    #define BOARD_SDA_PIN                       (17)
    #define BOARD_SCL_PIN                       (18)
    #define ADC_BUTTONS_PIN                     (7)
    #define MODEM_RX_PIN                        (4)
    #define MODEM_TX_PIN                        (6)
    #define MODEM_DTR_PIN                       (5)
    #define MODEM_RING_PIN                      (1)
    #define BOARD_PWRKEY_PIN                    (3)
    #define GPS_RX_PIN                          (39)
    #define GPS_TX_PIN                          (42)
    #define BOARD_LED_PIN                       (38)
    #define LED_ON                              (HIGH)
    #define SerialAT                            Serial1
    #ifndef MODEM_GPS_ENABLE_GPIO
      #define MODEM_GPS_ENABLE_GPIO             (-1)
    #endif
    #ifndef MODEM_GPS_ENABLE_LEVEL
      #define MODEM_GPS_ENABLE_LEVEL            (-1)
    #endif
#endif

#if defined(TINY_GSM_MODEM_SIM7670G) || defined(TINY_GSM_MODEM_A7670) || defined(TINY_GSM_MODEM_A7608)
    #define MODEM_REG_SMS_ONLY
#endif

#if defined(TINY_GSM_MODEM_A7670)
    #define MODEM_POWERON_PULSE_WIDTH_MS        (100)
    #define MODEM_POWEROFF_PULSE_WIDTH_MS       (3000)
#elif defined(TINY_GSM_MODEM_SIM7670G)
    #define MODEM_POWERON_PULSE_WIDTH_MS        (100)
    #define MODEM_POWEROFF_PULSE_WIDTH_MS       (3000)
#elif defined(TINY_GSM_MODEM_SIM7600)
    #define MODEM_POWERON_PULSE_WIDTH_MS        (500)
    #define MODEM_POWEROFF_PULSE_WIDTH_MS       (3000)
    #define MODEM_START_WAIT_MS                 (15000)
#elif defined(TINY_GSM_MODEM_SIM7080)
    #define MODEM_POWERON_PULSE_WIDTH_MS        (1000)
    #define MODEM_POWEROFF_PULSE_WIDTH_MS       (1300)
#elif defined(TINY_GSM_MODEM_A7608)
    #define MODEM_POWERON_PULSE_WIDTH_MS        (1000)
    #define MODEM_POWEROFF_PULSE_WIDTH_MS       (3000)
#elif defined(TINY_GSM_MODEM_SIM7000SSL) || defined(TINY_GSM_MODEM_SIM7000)
    #define MODEM_POWERON_PULSE_WIDTH_MS        (1000)
    #define MODEM_POWEROFF_PULSE_WIDTH_MS       (1300)
#endif

#ifndef MODEM_START_WAIT_MS
    #define MODEM_START_WAIT_MS                 (3000)
#endif
