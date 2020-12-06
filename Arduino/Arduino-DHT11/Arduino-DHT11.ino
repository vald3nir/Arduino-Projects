#include "DHT.h" // https://github.com/adafruit/DHT-sensor-library

#define DHTPIN A2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print(" Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
  delay(1000);
}
