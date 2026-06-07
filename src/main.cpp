#include <Arduino.h>
#include "smart_home.h"
#include "Button.h"
#include "LightController.h"
#include "HMIPanel.h"

const int CONST_POWER_PIN = 15; 

const int CONST_BUTTON_PIN1 = 4;

const int CONST_LED_PIN1 = 16;

Button LightSwitch(CONST_BUTTON_PIN1);
LightController roomLight(CONST_LED_PIN1);


void setup() {
  Serial.begin(115200);
  pinMode(CONST_POWER_PIN, OUTPUT);
  digitalWrite(CONST_POWER_PIN, HIGH); 
  LightSwitch.init();
  roomLight.init();

}

void loop() {
  int mainClickType = LightSwitch.checkClicks();
  if (mainClickType == 1) {
      roomLight.toggle();
  } else if (mainClickType == 2) {
      roomLight.setBrightness(100);
  } else if (mainClickType == 3) {
      roomLight.setBrightness(-100);
  }

}