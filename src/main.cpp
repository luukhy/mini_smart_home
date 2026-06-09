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
const int CONST_ROOM_LIGHTS_LED_PIN = 16;
const int CONST_HUMIDITY_ALERT_LED_PIN = 19;

const float CONST_TEMPERATURE_GOAL = 23; 
const float CONST_HUMIDITY_GOAL = 50; 

const int CONST_TEMPERATURE_TOL = 3;
const int CONST_HUMIDITY_TOL = 10;

const int CONST_MIN_TEMPERATURE = CONST_TEMPERATURE_GOAL - CONST_TEMPERATURE_TOL;
const int CONST_MAX_TEMPERATURE = CONST_TEMPERATURE_GOAL + CONST_TEMPERATURE_TOL;

const int CONST_MIN_HUMIDITY = CONST_HUMIDITY_GOAL - CONST_HUMIDITY_TOL;
const int CONST_MAX_HUMIDITY = CONST_HUMIDITY_GOAL + CONST_HUMIDITY_TOL;

Button light_switch(CONST_BUTTON_PIN1);
Button hmi_button(CONST_HMI_BUTTON);

LightController room_light(CONST_ROOM_LIGHTS_LED_PIN);
LightController humidity_alarm(CONST_HUMIDITY_ALERT_LED_PIN);

bool humidity_alarm_on = false;
bool temperature_alarm_on = false;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
HMIPanel hmi_panel(LIGHTS, &lcd);

DHT dht(DHTPIN, DHTTYPE);

unsigned long last_dht_time = 0;
const unsigned long dht_interval = 2000;

float humidity = CONST_HUMIDITY_GOAL;
float temperature = CONST_TEMPERATURE_GOAL;

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
  humidity_alarm.init();

  hmi_panel.display();
  if (hmi_panel.getPage() == LIGHTS) {
    hmi_panel.drawProgressBar(room_light.getBrightness(), 0, 100, 1, 16);
  }
}

void loop() {
  unsigned long current_time = millis();

  humidity_alarm_on = !fInRange(humidity, CONST_MIN_HUMIDITY, CONST_MAX_HUMIDITY);

  if (humidity_alarm_on) {
    humidity_alarm.on();
    int speed_factor = 4; 
    int cycle = (current_time / speed_factor) % 512; 
    int alarm_led_lvl = (cycle > 255) ? (511 - cycle) : cycle; 
    
    humidity_alarm.setBrightness(alarm_led_lvl);
  } else {
    humidity_alarm.off();
  }

  if (current_time - last_dht_time >= dht_interval) {
    last_dht_time = current_time;
    
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    
    if (hmi_panel.getPage() == ENV) { 
      hmi_panel.refresh_dht(humidity, temperature);
    }
  }

  if (hmi_button.isPressed()) {
    hmi_panel.nextPage();
    
    if (hmi_panel.getPage() == LIGHTS) {
      hmi_panel.drawProgressBar(room_light.getBrightness(), 0, 100, 1, 16);
    }
  }
  
  int main_click_type = light_switch.checkClicks();
  if (main_click_type == 1) {
      room_light.toggle();
  } else if (main_click_type == 2) {
      room_light.adjustBrightness(50);
  } else if (main_click_type == 3) {
      room_light.adjustBrightness(-50);
  }
  
  if (main_click_type > 0) {
      hmi_panel.setLightsLevel(room_light.getBrightness());
      
      if (hmi_panel.getPage() == LIGHTS) {
          hmi_panel.display(); 
          hmi_panel.drawProgressBar(room_light.getBrightness(), 0, 100, 1, 16); 
      }
  }
}