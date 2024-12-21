#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Definir as credenciais da rede WiFi
const char* ssid = "Dev Severino";
const char* password = "17210000";

// Definir o pino GPIO conectado à chama
const int pino_chama = D1;  // GPIO 5

// Inicializar o servidor web na porta 80
ESP8266WebServer server(80);

// Função para ligar a chama
void ligarChama() {
  digitalWrite(pino_chama, HIGH);
  server.send(200, "text/plain", "Chama acesa!");
}

// Função para desligar a chama
void desligarChama() {
  digitalWrite(pino_chama, LOW);
  server.send(200, "text/plain", "Chama apagada!");
}

void setup() {
  // Inicializar o pino GPIO como saída
  pinMode(pino_chama, OUTPUT);
  digitalWrite(pino_chama, LOW);

  // Inicializar a comunicação serial
  Serial.begin(115200);

  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  Serial.println("");

  // Esperar até estar conectado à rede WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado à rede WiFi ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Definir rotas para ligar e desligar a chama
  server.on("/ligar", ligarChama);
  server.on("/desligar", desligarChama);

  // Iniciar o servidor
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  // Lidar com as solicitações dos clientes
  server.handleClient();
}


/*
Test -> curl --location '192.168.1.111/ligar'
        curl --location '192.168.1.111/desligar'
*/




