#include <Arduino.h>
#include <ezButton.h>
#include "RF24.h"
#include "esp_wifi.h"

SPIClass *hp = nullptr;
RF24 radio(16, 15, 16000000);
byte i = 45;
unsigned int flag = 0;
ezButton toggleSwitch(33);

void initHP()
{
  hp = new SPIClass(HSPI);
  hp->begin();
  if (radio.begin(hp))
  {
    delay(200);
    Serial.println("Hp Started !!!");
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPayloadSize(5);
    radio.setAddressWidth(3);
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.printPrettyDetails();
    radio.startConstCarrier(RF24_PA_MAX, i);
  }
  else
  {
    Serial.println("HP couldn't start !!");
  }
}

void two()
{
  if (flag == 0)
  {
    i += 2;
  }
  else
  {
    i -= 2;
  }
  if ((i > 79) && (flag == 0))
  {
    flag = 1;
  }
  else if ((i < 2) && (flag == 1))
  {
    flag = 0;
  }
  radio.setChannel(i);
}

void one()
{
  for (int i = 0; i < 79; i++)
  {
    radio.setChannel(i);
  }
}

void setup()
{
  esp_wifi_stop(); // Apenas desativamos o Wi-Fi, já que não há Bluetooth
  esp_wifi_deinit();
  Serial.begin(115200);
  toggleSwitch.setDebounceTime(50);
  initHP();
}

void loop()
{
  toggleSwitch.loop();
  int state = toggleSwitch.getState();
  if (state == HIGH)
    two();
  else
    one();
}