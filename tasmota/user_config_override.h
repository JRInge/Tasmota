/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

// force the compiler to show a warning to confirm that this file is included
#warning **** user_config_override.h: Using Settings from this File ****

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*
Examples :

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "your-mqtt-server.com" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "YourMqttUser"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "YourMqttPass"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef MY_IP
#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS     MY_IP                // Set to 0.0.0.0 for using DHCP or enter a static IP address
#endif

#ifdef MY_GW
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY        MY_GW                // if not using DHCP set Gateway IP address
#endif

#ifdef MY_DNS
#undef  WIFI_DNS
#define WIFI_DNS            MY_DNS               // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

// !!! Remember that your changes GOES AT THE BOTTOM OF THIS FILE right before the last #endif !!!
*/

#undef  NTP_SERVER1
#define NTP_SERVER1         "europe.pool.ntp.org"
#undef  NTP_SERVER2
#define NTP_SERVER2         "uk.pool.ntp.org"
#undef  NTP_SERVER3
#define NTP_SERVER3         "nl.pool.ntp.org"
#undef  TIME_DST_HOUR
#define TIME_DST_HOUR       1
#undef  TIME_DST_OFFSET
#define TIME_DST_OFFSET     +60
#undef  TIME_STD_HOUR
#define TIME_STD_HOUR       2
#undef  TIME_STD_OFFSET
#define TIME_STD_OFFSET     0
#undef  APP_TIMEZONE
#define APP_TIMEZONE        99                   // [Timezone] +1 hour (Amsterdam) (-13 .. 14 = hours from UTC, 99 = use TIME_DST/TIME_STD)
#undef  LATITUDE
#define LATITUDE            51.479761
#undef  LONGITUDE
#define LONGITUDE           -2.634318

#ifdef  USE_DOMOTICZ
#undef  USE_DOMOTICZ                             // Enable Domoticz (+6k code, +0.3k mem)
#endif
#ifndef USE_JAVASCRIPT_ES6
#define USE_JAVASCRIPT_ES6                       // Enable ECMAScript6 syntax using less JavaScript code bytes (fails on IE11)
#endif
#ifdef  USE_EMULATION_HUE
#undef  USE_EMULATION_HUE                        // Disable Hue Bridge emulation for Alexa (+14k code, +2k mem common)
#endif
#ifdef  USE_EMULATION_WEMO
#undef  USE_EMULATION_WEMO                       // Disable Belkin WeMo emulation for Alexa (+6k code, +2k mem common)
#endif

// -- mDNS ----------------------------------------
#ifdef  MDNS_ENABLED
#undef  MDNS_ENABLED
#endif
#define MDNS_ENABLED        true                 // [SetOption55] Use mDNS (false = Disable, true = Enable)
#ifndef USE_DISCOVERY
#define USE_DISCOVERY                            // Enable mDNS for the following services (+8k code or +23.5k code with core 2_5_x, +0.3k mem)
#ifndef WEBSERVER_ADVERTISE
#define WEBSERVER_ADVERTISE                      // Provide access to webserver by name <Hostname>.local/
#endif
#ifndef MQTT_HOST_DISCOVERY
#define MQTT_HOST_DISCOVERY                      // Find MQTT host server (overrides MQTT_HOST if found)
#endif

// -- Ping ----------------------------------------
#ifndef USE_PING
#define USE_PING                                 // Enable Ping command (+2k code)
#endif

// ***********************************************
// ** Firmare specific settings ******************

// -- Options for firmware tasmota-up111 ------

/*
Component	 Old GPIO 	New GPIO	Description
LedLinki   158        576       Device Status LED, inverted
Button1		 17	        32        Button active low, internal pull-up resistor
BL0937 CF	 134        2720      BL0937 Single Phase Energy Monitor Chip CF pin
HLWBL CF1	 132        2656      Energy Monitoring (for example Pow)
HLWBL SELi 131        2624      Energy Monitoring (for example Pow)
Led1i      56         320       Inverted LED - default state ON
Relay1     21         224       Relay
*/

#ifdef FIRMWARE_UP111
    // This line will issue a warning during the build (yellow in
    // VSCode) so you see which section is used
    #warning **** Build: UP111 ****
    // -- CODE_IMAGE_STR is the name shown between brackets on the
    //    Information page or in INFO MQTT messages
    #undef  CODE_IMAGE_STR
    #define CODE_IMAGE_STR "up111"

    // Put here your override for firmware tasmota-up111
    #ifdef  USE_I2C
    #undef  USE_I2C

    // -- Optional modules ----------------------------
    #ifdef  ROTARY_V1
    #undef  ROTARY_V1                                // Remove support for Rotary Encoder as used in MI Desk Lamp (+0k8 code)
    #endif
    #ifdef  USE_SONOFF_RF
    #undef  USE_SONOFF_RF                            // Remove support for Sonoff Rf Bridge (+3k2 code)
    #endif
    #ifdef  USE_SONOFF_SC
    #undef  USE_SONOFF_SC                            // Remove support for Sonoff Sc (+1k1 code)
    #endif
    #ifdef  USE_TUYA_MCU
    #undef  USE_TUYA_MCU                             // Remove support for Tuya Serial MCU
    #endif
    #ifdef  USE_ARMTRONIX_DIMMERS
    #undef  USE_ARMTRONIX_DIMMERS                    // Remove support for Armtronix Dimmers (+1k4 code)
    #endif
    #ifdef  USE_PS_16_DZ
    #undef  USE_PS_16_DZ                             // Remove support for PS-16-DZ Dimmer (+2k code)
    #endif
    #ifdef  USE_SONOFF_IFAN
    #undef  USE_SONOFF_IFAN                          // Remove support for Sonoff iFan02 and iFan03 (+2k code)
    #endif
    #ifdef  USE_BUZZER
    #undef  USE_BUZZER                               // Remove support for a buzzer (+0k6 code)
    #endif
    #ifdef  USE_ARILUX_RF
    #undef  USE_ARILUX_RF                            // Remove support for Arilux RF remote controller (+0k8 code, 252 iram (non 2.3.0))
    #endif
    #ifdef  USE_SHUTTER
    #undef  USE_SHUTTER                              // Remove Shutter support for up to 4 shutter with different motortypes (+11k code)
    #endif
    #ifdef  USE_EXS_DIMMER
    #undef  USE_EXS_DIMMER                           // Remove support for ES-Store Wi-Fi Dimmer (+1k5 code)
    #endif
    #ifdef  USE_PWM_DIMMER
    #undef  USE_PWM_DIMMER                           // Remove support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+2k3 code, DGR=0k7)
    #endif
    #ifdef  USE_SONOFF_D1
    #undef  USE_SONOFF_D1                            // Remove support for Sonoff D1 Dimmer (+0k7 code)
    #endif
    #ifdef  USE_SHELLY_DIMMER
    #undef  USE_SHELLY_DIMMER                        // Remove support for Shelly Dimmer (+3k code)
    #endif

    // -- Optional light modules ----------------------
    #ifdef  USE_LIGHT
    #undef  USE_LIGHT                                // Remove support for light control
    #endif
    #ifdef  USE_WS2812
    #undef  USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //
    #endif
    #ifdef  USE_MY92X1
    #undef  USE_MY92X1                               // Remove support for MY92X1 RGBCW led controller as used in Sonoff B1, Ailight and Lohas
    #endif
    #ifdef  USE_SM16716
    #undef  USE_SM16716                              // Remove support for SM16716 RGB LED controller (+0k7 code)
    #endif
    #ifdef  USE_SM2135
    #undef  USE_SM2135                               // Remove support for SM2135 RGBCW led control as used in Action LSC (+0k6 code)
    #endif
    #ifdef  USE_SONOFF_L1
    #undef  USE_SONOFF_L1                            // Remove support for Sonoff L1 led control
    #endif
    #ifdef  USE_ELECTRIQ_MOODL
    #undef  USE_ELECTRIQ_MOODL                       // Remove support for ElectriQ iQ-wifiMOODL RGBW LED controller (+0k3 code)
    #endif
    #ifdef  USE_LIGHT_PALETTE
    #undef  USE_LIGHT_PALETTE                        // Remove support for color palette (+0k7 code)
    #endif
    #ifdef  USE_LIGHT_VIRTUAL_CT
    #undef  USE_LIGHT_VIRTUAL_CT                     // Remove support for Virtual White Color Temperature (+1.1k code)
    #endif
    #ifdef  USE_DGR_LIGHT_SEQUENCE
    #undef  USE_DGR_LIGHT_SEQUENCE                   // Remove support for device group light sequencing (requires USE_DEVICE_GROUPS) (+0k2 code)
    #endif

    // -- Power monitoring sensors --------------------
    #ifndef USE_ENERGY_SENSOR
    #define USE_ENERGY_SENSOR                        // Add support for Energy Monitors (+14k code)
    #endif
    #ifndef USE_HLW8012
    #define USE_HLW8012                              // Add support for HLW8012, BL0937 or HJL-01 Energy Monitor for Sonoff Pow and WolfBlitz
    #endif
    #ifdef  USE_CSE7766
    #undef  USE_CSE7766                              // Remove support for CSE7766 Energy Monitor for Sonoff S31 and Pow R2
    #endif
    #ifdef  USE_PZEM004T
    #undef  USE_PZEM004T                             // Remove support for PZEM004T Energy monitor (+2k code)
    #endif
    #ifdef  USE_PZEM_AC
    #undef  USE_PZEM_AC                              // Remove support for PZEM014,016 Energy monitor (+1k1 code)
    #endif
    #ifdef  USE_PZEM_DC
    #undef  USE_PZEM_DC                              // Remove support for PZEM003,017 Energy monitor (+1k1 code)
    #endif
    #ifdef  USE_MCP39F501
    #undef  USE_MCP39F501                            // Remove support for MCP39F501 Energy monitor as used in Shelly 2 (+3k1 code)
    #endif
    #ifdef  USE_BL0940
    #undef  USE_BL0940                               // Remove support for BL0940 Energy monitor as used in Blitzwolf SHP-10 (+1k6 code)
    #endif

    // -- Low level interface devices -----------------
    #ifdef  USE_DHT
    #undef  USE_DHT                                  // Remove support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor (1k6 code)
    #endif

    // -- IR Remote features - all protocols from IRremoteESP8266 --------------------------
    // Further configuration required to enable full IR protocols.
    #ifdef  USE_IR_REMOTE
    #undef  USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 (+4k3 code, 0k3 mem, 48 iram)
    #endif

#endif

// -- Options for firmware tasmota32-d1 ------
#ifdef FIRMWARE_D1

    // If these settings are only for ESP32, you can check these
    // are used only when building for ESP32
    #ifndef ESP32
    #error *** This setup is for tasmota32 only ***
    #endif

    #warning **** Build: D1 ****
    #undef CODE_IMAGE_STR
    #define CODE_IMAGE_STR "mini-d1-esp32"

    // Put here your override for firmware tasmota32-mini-d1-esp32

#endif




#endif  // _USER_CONFIG_OVERRIDE_H_
