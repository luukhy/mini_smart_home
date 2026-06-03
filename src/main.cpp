#include <Arduino.h>
#include <LiquidCrystal.h>

const int rs = 13;
const int en = 14;
const int d4 = 27;
const int d5 = 26;
const int d6 = 25;
const int d7 = 33;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200);
  Serial.println("Inicjalizacja LCD...");

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Smart Home:");
  
  lcd.setCursor(0, 1);
  lcd.print("System Gotowy!");
}

void loop() {
  delay(1000);
  lcd.setCursor(14, 1);
  lcd.print(".");
  delay(1000);
  lcd.setCursor(15, 1);
  lcd.print(".");
  delay(1000);
  
  lcd.setCursor(14, 1);
  lcd.print("  "); 
}