#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#include "HMIPanel.h"
#include "smart_home.h"

const int RS = 13, EN = 14, D4 = 27, D5 = 26, D6 = 25, D7 = 33;
const int HMI_SWITCH_IN_PIN = 32;
const unsigned long CONST_DEBOUNCE_DELAY = 50;
const int DHTPIN = 22;
const uint8_t DHTTYPE = DHT11;

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
  pinMode(HMI_SWITCH_IN_PIN, INPUT_PULLUP);

  hmi_panel.display();
}

void loop() {
  int value = debounce(HMI_SWITCH_IN_PIN, button_state, last_button_state, last_debounce_time, CONST_DEBOUNCE_DELAY);
  if(value) {
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
}