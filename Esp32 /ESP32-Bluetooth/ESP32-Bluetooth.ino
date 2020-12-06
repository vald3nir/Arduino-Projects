// REF: https://www.dobitaobyte.com.br/comunicacao-serial-usando-bluetooth-no-esp32/

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
uint8_t counter = 0;

void setup()
{
  Serial.begin(9600);
  SerialBT.begin("ESP32");
}

void loop()
{
  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {
    Serial.write(SerialBT.read());
  }
  delay(2000);
  SerialBT.write(counter);
  counter = counter > 254 ? 0 : counter + 1;
}
