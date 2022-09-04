#ifndef _PRST_CONFIG_H_
#define _PRST_CONFIG_H_

#include "nrf_gpio.h"
// Some configurations are version-specific. Uncomment the line corresponding
// the version you're programming. The version can be found on the
// b-parasite board.
// #define PRST_VERSION_1_0_X
// #define PRST_VERSION_1_1_X
#define PRST_VERSION_1_2_X

// Built-in LED.
// Weather or not to turn the LED on/off during the wake-up cycle. Impacts
// battery life.
#define PRST_BLINK_LED 1
#define PRST_LED_PIN NRF_GPIO_PIN_MAP(0, 28)

// Deep sleep.
#define PRST_DEEP_SLEEP_IN_SECONDS 600

// Analog to digital converter (ADC).
// Prints out ADC debug info, such as the values read for battery and soil
// moisture.
#define PRST_ADC_BATT_DEBUG 0
#define PRST_ADC_SOIL_DEBUG 0

// BLE.
// Prints out BLE debug info, such as the final encoded advertisement packet.
#define PRST_BLE_DEBUG 0

// Supported BLE protocols.
// Default, custom BLE protocol.
#define PRST_BLE_PROTOCOL_BPARASITE_V2 0x01
// BTHome BLE protocol - https://bthome.io.
#define PRST_BLE_PROTOCOL_BTHOME 0x02

// Chosen BLE protocol.
#define PRST_BLE_PROTOCOL PRST_BLE_PROTOCOL_BPARASITE_V2

// There are two options for configuring the MAC address of b-parasites:
// 1. Comment out the PRST_BLE_MAC_ADDR to use a random static MAC address that
// is preprogrammed in each nRF52 chip.
// 2. Manually specify the MAC address you want below. In this scenario, the
// following constraints must be met to ensure valid random static MAC
// addresses:
// a. Two most significant bits are set to 1;
// b. The remaining bits should not _all_ be set to 0;
// c. The remaining bits should not _all_ be set to 1;
// #define PRST_BLE_MAC_ADDR "f0:ca:f0:ca:01:01"

// This name decodes as 🌱
#define PRST_BLE_ADV_NAME "\xf0\x9f\x8c\xb1" 
// Total time spend advertising.
#define PRST_BLE_ADV_TIME_IN_S 1
// Interval between advertising packets.
// From the specs, this value has to be greater or equal 20ms.
#define PRST_BLE_ADV_INTERVAL_IN_MS 30
// Possible values are ..., -8, -4, 0, 4, 8.
#define PRST_BLE_ADV_TX_POWER 8
// Experimental support for "long range" BLE, introduced in Bluetooth 5. It uses
// a different type of physical layer - the Coded PHY. Receivers should also
// scan using Coded PHY in order to find this device when operating in this
// mode.
#define PRST_BLE_EXPERIMENTAL_LONG_RANGE 0

// PWM.
#define PRST_PWM_PIN NRF_GPIO_PIN_MAP(0, 5)

#ifdef NRF52833_XXAA
#define PRST_FAST_DISCH_PIN NRF_GPIO_PIN_MAP(0, 25)
#else
#define PRST_FAST_DISCH_PIN NRF_GPIO_PIN_MAP(1, 10)
#endif

// SHT3C temp/humidity sensor.
#define PRST_SHT3C_DEBUG 0

// Version-specific configuration.
#if defined(PRST_VERSION_1_1_X)
// The photoresistor (LDR) is optional in this revision. If set to 1, the LDR's
// ADC channel will be sampled and its data will be encoded in the BLE
// advertisement packet.
#define PRST_HAS_LDR 1

// Light sensor pins.
#define PRST_PHOTO_V_PIN NRF_GPIO_PIN_MAP(0, 29)
#define PRST_PHOTO_OUT_PIN NRF_GPIO_PIN_MAP(0, 2)

// Whether to produce debug messages for the LDR
#define PRST_ADC_PHOTO_DEBUG 0

#elif defined(PRST_VERSION_1_2_X)

#define PRST_HAS_PHOTOTRANSISTOR 1

#define PRST_PHOTO_V_PIN NRF_GPIO_PIN_MAP(0, 29)
#define PRST_PHOTO_OUT_PIN NRF_GPIO_PIN_MAP(0, 2)

#define PRST_ADC_PHOTO_DEBUG 0

#endif  // End of version-specific configuration.

#endif  // _PRST_CONFIG_H_
