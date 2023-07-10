#ifndef PWM_CONTROLLER_ESP32_H
#define PWM_CONTROLLER_ESP32_H

#define RX_PIN 2
#define TX_PIN 3
#define SERIAL_BAUD_RATE 9600

//#define DEBUG

#ifdef DEBUG
#define DBGLOG(msg) debugSerial.write(msg)
#else
#define DBGLOG(msg)
#endif

#ifdef ESP32
#define LED_LOW HIGH
#define LED_HIGH LOW
#include <WiFi.h>
#include <HardwareSerial.h>
#define pwmSerial Serial
#ifdef DEBUG
#define debugSerial Serial1
#endif
#else
#define LED_LOW LOW
#define LED_HIGH HIGH
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial pwmSerial(RX_PIN, TX_PIN);
#ifdef DEBUG
#define debugSerial pwmSerial
#endif
#endif

#include <WiFiClientSecure.h>

// Universal Telegram Bot Library written by Brian Lough:
// https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

static void setupSerial()
{
#ifdef DEBUG
  debugSerial.begin(SERIAL_BAUD_RATE);
#endif
  DBGLOG("setup");
#ifdef DEBUG
  if (pwmSerial != debugSerial)
#endif
  {
    pwmSerial.begin(SERIAL_BAUD_RATE);
  }
}

static void setupWiFi()
{
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  pinMode(LED_BUILTIN, OUTPUT);
  auto state = LED_LOW;
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, state);
    delay(500);
    state ^= LED_HIGH;
    digitalWrite(LED_BUILTIN, state);
    delay(500);
    state ^= LED_HIGH;
  }
}

#endif // PWM_CONTROLLER_ESP32_H
