#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Dev Severino";
const char *password = "17210000";

const char *mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char *mqttTopicSubscriber = "vald3nir/led/status/";
const char *mqttTopicPublisher = "vald3nir/sensor/status/";

int ledPin = 13; // GPIO13---D7 of NodeMCU
bool ledState = false;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  if (ledState == false)
  {
    ledState = true;
    digitalWrite(ledPin, HIGH);
    client.publish(mqttTopicPublisher, "LED Ligado");
  }
  else
  {
    ledState = false;
    digitalWrite(ledPin, LOW);
    client.publish(mqttTopicPublisher, "LED Desligado");
  }
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println();
  Serial.print("Conectando-se ao WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado ao WiFi");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected())
  {
    Serial.println("Conectando-se ao MQTT...");

    if (client.connect("NodeMCUClient"))
    {
      Serial.println("Conectado ao MQTT");
      client.subscribe(mqttTopicSubscriber);
    }
    else
    {
      Serial.print("Falha ao conectar. Código de erro: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void loop()
{
  client.loop();
}