#include <WiFi.h>
#include "PubSubClient.h"

// ---------------------------------------------------------------------------

// Wi-fi Setup
const char *SSID = "dev severino";
const char *PASSWORD = "17210000";

// MQTT Setup
#define TOPIC_PUBLISH "esp32/mqtt/test/publish"
#define TOPIC_SUBSCRIBER "esp32/mqtt/test/subscriber"
#define ID_MQTT "1234567890"

const char *BROKER_MQTT = "broker.hivemq.com";
int BROKER_PORT = 1883;

// ---------------------------------------------------------------------------

WiFiClient espClient;
PubSubClient MQTT(espClient);

// ---------------------------------------------------------------------------

void initWiFi(void);
void initMQTT(void);
void mqtt_callback(char *topic, byte *payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void VerificaConexoesWiFIEMQTT(void);

// ---------------------------------------------------------------------------

void initWiFi(void)
{
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");

  reconnectWiFi();
}

// ---------------------------------------------------------------------------

void initMQTT(void)
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);
}

// ---------------------------------------------------------------------------

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  String msg;

  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.print("Chegou a seguinte string via MQTT: ");
  Serial.println(msg);
}

// ---------------------------------------------------------------------------

void reconnectMQTT(void)
{
  while (!MQTT.connected())
  {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT))
    {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe(TOPIC_SUBSCRIBER);
    }
    else
    {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Havera nova tentatica de conexao em 2s");
      delay(2000);
    }
  }
}

// ---------------------------------------------------------------------------

void VerificaConexoesWiFIEMQTT(void)
{
  if (!MQTT.connected())
  {
    reconnectMQTT();
  }
  reconnectWiFi();
}

// ---------------------------------------------------------------------------

void reconnectWiFi(void)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    return;
  }
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso na rede ");
  Serial.print(SSID);
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}

// ---------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  initWiFi();
  initMQTT();
}

void loop()
{
  char payload[10] = {0};

  VerificaConexoesWiFIEMQTT();

  sprintf(payload, "%.2fC", 1721.0f);

  MQTT.publish(TOPIC_PUBLISH, payload);
  MQTT.loop();

  delay(2000);
}
