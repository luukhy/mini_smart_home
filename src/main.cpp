#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#include "HMIPanel.h"
#include "smart_home.h"
#include "Button.h"
#include "LightController.h"
#include "HMIPanel.h"

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

int last_button_state = HIGH;
int button_state = HIGH;
unsigned long last_debounce_time = 0;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);  
  dht.begin();
  pinMode(CONST_HMI_BUTTON, INPUT_PULLUP);


  pinMode(CONST_POWER_PIN, OUTPUT);
  digitalWrite(CONST_POWER_PIN, HIGH); 
  light_switch.init();
  room_light.init();

  hmi_panel.display();
}

void loop() {
  if(hmi_button.isPressed()) {
    hmi_panel.nextPage();
  }

  unsigned long currentTime = millis();
    if (currentTime - last_dht_time >= dht_interval) {
        last_dht_time = currentTime;

        float h = dht.readHumidity();
        float t = dht.readTemperature();

        if (!isnan(h) && !isnan(t)) {
            hmi_panel.setTemperature((int)t);
            hmi_panel.setHumidity((int)h);

          if (hmi_panel.getPage() == ENV) {
              hmi_panel.display(); 
          }
        } else {
            Serial.println("Blad odczytu z DHT11!");
        }
    }
  int main_click_type = light_switch.checkClicks();
  if (main_click_type == 1) {
      room_light.toggle();
  } else if (main_click_type == 2) {
      room_light.setBrightness(100);
  } else if (main_click_type == 3) {
      room_light.setBrightness(-100);
  }

}