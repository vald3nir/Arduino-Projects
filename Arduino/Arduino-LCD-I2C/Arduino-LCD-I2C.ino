// REF: https://www.arduinoecia.com.br/modulo-i2c-display-16x2-arduino/

#include <Wire.h>
#include "LiquidCrystal_I2C.h"

// Pinagem do I2C do Ardunino UNO ->     Verde: A5, Azul: A4 Branco: 0V Roxo: 5V

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup()
{
  lcd.begin (16, 2);
}


void loop() {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Arduino e Cia !!");
  lcd.setCursor(0, 1);
  lcd.print("LCD e modulo I2C");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
}
