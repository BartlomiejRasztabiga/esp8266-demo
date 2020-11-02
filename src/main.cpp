#include <Arduino.h>
#include "Adafruit_Sensor.h"
#include "DHT.h"

#define DHTTYPE DHT11
#define DHTPIN D1

DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float h = 0.0;

unsigned long previousMillis = 0;

const long interval = 10000;

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(DHTPIN, INPUT);

  dht.begin();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature(false);
    // if temperature read failed, don't change t value
    if (isnan(newT))
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value
    if (isnan(newH))
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
      h = newH;
      Serial.println(h);
    }
  }
}