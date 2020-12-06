int pinoLed = 12;   // PINO DIGITAL UTILIZADO PELO LED
int pinoSensor = 3; // PINO DIGITAL UTILIZADO PELO SENSOR
int estadoSensor;   // VARIÁVEL QUE ARMAZENA O ESTADO DA SAÍDA DO SENSOR (HIGH / LOW)

void setup()
{
  Serial.begin(9600);
  pinMode(pinoSensor, INPUT); // DEFINE O PINO COMO ENTRADA
  pinMode(pinoLed, OUTPUT);   // DEFINE O PINO COMO SAÍDA
}

void loop()
{
  int s = digitalRead(pinoSensor);

  if (s == HIGH)
  { // SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ
    estadoSensor = digitalRead(pinoLed);
    Serial.println(s);
    // LÊ O ESTADO ATUAL DO PINO E ARMAZENA NA VARIÁVEL
    digitalWrite(pinoLed, !estadoSensor); // MUDA O ESTADO ATUAL DO LED COMPARANDO COM O ESTADO
    // ARMAZENADO NA VARIÁVEL estadoSensor
    delay(500); // INTERVALO DE 500 MILISSEGUNDOS
  }
}
