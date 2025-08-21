// STM32 Nucleo-C031C6 I2C Example
// Simulation: https://wokwi.com/projects/365421666018061313

#include "LiquidCrystal_I2C.h"

#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, STM32!");

  lcd.init();
  lcd.backlight();

  lcd.setCursor(4, 0);
  lcd.print("Hello, STM32");
  lcd.setCursor(5, 2);
  lcd.print("Welcome to");
  lcd.setCursor(7, 3);
  lcd.print("Wokwi!");
}

void loop() {
  lcd.setCursor(0, 1);   // Columna 0, fila 1
  lcd.print("Linea 2 completa");

  lcd.setCursor(10, 2);  // Columna 10, fila 2
  lcd.print("Extra");

  delay(2000);

  lcd.setCursor(0, 3);   // Columna 0, fila 3
  lcd.print("Texto final");
}

