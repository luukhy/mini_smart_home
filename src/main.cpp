#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#include "HMIPanel.h"
#include "smart_home.h"
#include "Button.h"
#include "LightController.h"

const int RS = 13, EN = 14, D4 = 27, D5 = 26, D6 = 25, D7 = 33;
const int CONST_HMI_BUTTON = 32;

const int DHTPIN = 22;
const uint8_t DHTTYPE = DHT11;

const int CONST_POWER_PIN = 15; 
const int CONST_BUTTON_PIN1 = 4;
const int CONST_LED_PIN1 = 16;

Button light_switch(CONST_BUTTON_PIN1);
Button hmi_button(CONST_HMI_BUTTON);

LightController room_light(CONST_LED_PIN1);
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
HMIPanel hmi_panel(LIGHTS, &lcd);
DHT dht(DHTPIN, DHTTYPE);

unsigned long last_dht_time = 0;
const unsigned long dht_interval = 2000;


void setup() {
  Serial.begin(115200);
  
  lcd.begin(16, 2);  
  hmi_panel.init();
  dht.begin();
  
  pinMode(CONST_HMI_BUTTON, INPUT_PULLUP);
  pinMode(CONST_POWER_PIN, OUTPUT);
  digitalWrite(CONST_POWER_PIN, HIGH); 
  
  light_switch.init();
  room_light.init();

  hmi_panel.display();
  if (hmi_panel.getPage() == LIGHTS) {
    hmi_panel.drawProgressBar(room_light.getBrightness(), 0, 100, 1, 16);
  }
}

void loop() {
  unsigned long current_time = millis();

  if (current_time - last_dht_time >= dht_interval) {
    last_dht_time = current_time;
    
    if (hmi_panel.getPage() == ENV) {
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      hmi_panel.refresh_dht(h, t);
    }
  }

  if(hmi_button.isPressed()) {
    hmi_panel.nextPage();
    
    if (hmi_panel.getPage() == LIGHTS) {
      hmi_panel.drawProgressBar(room_light.getBrightness(), 0, 100, 1, 16);
    }
  }
  
  int main_click_type = light_switch.checkClicks();
  if (main_click_type == 1) {
      room_light.toggle();
  } else if (main_click_type == 2) {
      room_light.setBrightness(50); 
  } else if (main_click_type == 3) {
      room_light.setBrightness(-50);
  }
  
  if (main_click_type > 0) {
      hmi_panel.setLightsLevel(room_light.getBrightness());
      
      if (hmi_panel.getPage() == LIGHTS) {
          hmi_panel.display(); 
          
          hmi_panel.drawProgressBar(room_light.getBrightness(), 0, 100, 1, 16); 
      }
  }
}