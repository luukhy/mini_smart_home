#include <Arduino.h>
#include <LiquidCrystal.h>

#include "HMIPanel.h"

const int RS = 13;
const int EN = 14;
const int D4 = 27;
const int D5 = 26;
const int D6 = 25;
const int D7 = 33;

const int HMI_SWITCH_IN_PIN = 32;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
HMIPanel hmi_panel(LIGHTS, &lcd, HMI_SWITCH_IN_PIN);


void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);  

  pinMode(HMI_SWITCH_IN_PIN, INPUT_PULLUP);

  hmi_panel.display();
}

void loop() {
  hmi_panel.display();
  Serial.println(digitalRead(HMI_SWITCH_IN_PIN));
  delay(2000);
}