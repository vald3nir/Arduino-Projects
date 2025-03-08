#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*
Conexões do nRF24L01 com o Arduino Uno
nRF24L01	            Arduino Uno
VCC (3.3V)	            3.3V (NÃO usar 5V!)
GND	                    GND
CE	                    9
CSN	                    10
SCK	                    13
MOSI	                11
MISO	                12
IRQ (não obrigatório)	-
*/

#define CE_PIN 9   // Pino CE no Arduino Uno
#define CSN_PIN 10 // Pino CSN (SS)

RF24 radio(CE_PIN, CSN_PIN);

void setup()
{
    Serial.begin(115200);
    if (!radio.begin())
    {
        Serial.println("Falha ao inicializar o nRF24L01!");
    }

    radio.setPALevel(RF24_PA_MAX);
    radio.stopListening(); // Define como transmissor
}

void loop()
{
    byte payload[32];
    memset(payload, 0xFF, sizeof(payload)); // Preenche com 0xFF

    for (int i = 0; i <= 125; i++) // Testa canais Bluetooth (0 a 125)
    {
        radio.setChannel(i);
        Serial.print("Enviando pacotes no canal: ");
        Serial.println(i);

        radio.write(payload, sizeof(payload)); // Envia pacotes
        delayMicroseconds(100);                // Pequeno atraso para sobrecarregar o canal
    }
}
