#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "SerialCom.h"
#include "Types.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

particleSensorState_t state;

WiFiManager wifiManager;
WiFiClient wifiClient;

char identifier[24];

void setup() {
  Serial.begin(115200);
  my_homekit_setup();
}

void loop() {
  my_homekit_loop();
  delay(10);
}

//==============================
// Homekit setup and loop
//==============================

// access your homekit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_pm25_density;
extern "C" homekit_characteristic_t cha_air_quality;

static uint32_t next_heap_millis = 0;
static uint32_t next_report_millis = 0;

void my_homekit_setup() {
  arduino_homekit_setup(&config);
  Serial.begin(115200);
  SerialCom::setup();
  delay(3000);
  snprintf(identifier, sizeof(identifier), "VINDRIKTNING-%X", ESP.getChipId());
  WiFi.hostname(identifier);
  setupWifi();
  setupOTA();
}

void setupOTA() {
    ArduinoOTA.onStart([]() { Serial.println("Start"); });
    ArduinoOTA.onEnd([]() { Serial.println("\nEnd"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            Serial.println("End Failed");
        }
    });

    ArduinoOTA.setHostname(identifier);

    // This is less of a security measure and more a accidential flash prevention
    ArduinoOTA.setPassword(identifier);
    ArduinoOTA.begin();
}

void my_homekit_loop() {
  arduino_homekit_loop();
  ArduinoOTA.handle();
  SerialCom::handleUart(state);
  const uint32_t t = millis();
  if (t > next_report_millis) {
    // report sensor values every 10 seconds
    next_report_millis = t + 10 * 1000;
    if (state.valid) {
      my_homekit_report();
    }
  }
  if (t > next_heap_millis) {
    // show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
        ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

  }
}

void setupWifi() {
    wifiManager.setDebugOutput(false);
    WiFi.hostname(identifier);
    wifiManager.autoConnect(identifier);
}

void resetWifiSettingsAndReboot() {
    wifiManager.resetSettings();
    delay(3000);
    ESP.restart();
}

void my_homekit_report() {
  cha_pm25_density.value.float_value = state.avgPM25;
  int air_quality_val = 0;
  if (state.avgPM25 >= 250){
          air_quality_val = 5;
  } else if (state.avgPM25 >= 150){
          air_quality_val = 4;
  } else if (state.avgPM25 >= 55){
          air_quality_val = 3;
  } else if (state.avgPM25 >= 35){
          air_quality_val = 2;
  } else if (state.avgPM25 >= 12){
          air_quality_val = 1;
  }
  cha_air_quality.value.int_value = air_quality_val;
  homekit_characteristic_notify(&cha_pm25_density, cha_pm25_density.value);
  homekit_characteristic_notify(&cha_air_quality, cha_air_quality.value);
}
