#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include <DHT.h>

#define DHT_SENSOR_PIN 23
#define DHT_SENSOR_TYPE DHT11

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup()
{
  Serial.begin(115200);
  dht_sensor.begin(); // initialize the DHT sensor
  lcd.begin();
  lcd.setBacklight(HIGH);
}

void loop()
{
  float humi = dht_sensor.readHumidity();     // read humidity
  float tempC = dht_sensor.readTemperature(); // read temperature

  lcd.clear();
  // check whether the reading is successful or not
  if (isnan(tempC) || isnan(humi))
  {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  }
  else
  {
    lcd.setCursor(0, 0); // display position
    lcd.print("Temp: ");
    lcd.print(tempC); // display the temperature
    lcd.print("C");

    lcd.setCursor(0, 1); // display position
    lcd.print("Humi: ");
    lcd.print(humi); // display the humidity
    lcd.print("%");
  }

  // wait a 2 seconds between readings
  delay(2000);
}