#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SSD1306Wire.h"

#include "wifi.h"

SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_128_32);
long startMillis = millis();
long pausedMillis = 0;
String activity = "PZSP1";
int BUTTON_PIN = D3;

bool paused = false;

void connectToWifi()
{
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
}

int returnSeconds(long millis)
{
  return millis / 1000;
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(BUTTON_PIN, INPUT);

  connectToWifi();

  display.init();
}

int buttonPressed(uint8_t button)
{
  static uint16_t lastStates = 0;
  uint8_t state = digitalRead(button);
  if (state != ((lastStates >> button) & 1))
  {
    lastStates ^= 1 << button;
    return state == HIGH;
  }
  return false;
}

void loop()
{
  if (buttonPressed(BUTTON_PIN))
  {
    paused = !paused;
    if (paused)
    {
      pausedMillis = millis();
    }

    Serial.println("paused " + String(paused));
  }

  if (!paused)
  {
    long seconds = returnSeconds(millis() - startMillis);

    display.clear();
    display.drawString(0, 0, "Aktualna aktywnosc:");
    display.drawString(0, 8, activity);
    display.drawString(0, 16, "Czas trwania: " + String(seconds) + String("s"));
    display.display();
  }
  else
  {
    startMillis += millis() - pausedMillis;
  }

  delay(100);
}
