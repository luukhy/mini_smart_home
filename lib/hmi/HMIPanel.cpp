#include <Arduino.h>
#include "HMIPanel.h"



byte bar1[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 };
byte bar2[8] = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 };
byte bar3[8] = { 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C };
byte bar4[8] = { 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E };
byte bar5[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };

HMIPanel::HMIPanel(hmi_page page_mode, LiquidCrystal* lcd) 
    : m_page(page_mode), m_lcd(lcd), m_lights_level(0), 
      m_temperature(0), m_humidity(0) , m_refresh_rate(2000)
{}

HMIPanel::~HMIPanel() {}

void HMIPanel::init() {
    m_lcd->createChar(1, bar1);
    m_lcd->createChar(2, bar2);
    m_lcd->createChar(3, bar3);
    m_lcd->createChar(4, bar4);
    m_lcd->createChar(5, bar5);
}

void HMIPanel::display() {
    m_lcd->clear();
    switch (m_page) {
        case LIGHTS:
            m_lcd->setCursor(0, 0);
            m_lcd->print("Light level: ");
            m_lcd->print(m_lights_level);
            break;
            
        case ENV:
            m_lcd->setCursor(0, 0);
            m_lcd->print("Humidity: ");
            m_lcd->print(m_humidity);

            m_lcd->setCursor(0, 1);
            m_lcd->print("Temperature: ");
            m_lcd->print(m_temperature);
            break;

        default:
            break;
    }
}

void HMIPanel::nextPage() {
    int next_index = (static_cast<int>(m_page) + 1) % NUM_PAGES;
    m_page = static_cast<hmi_page>(next_index);

    display();
}

void HMIPanel::refresh_dht(float h, float t) {

        if (!isnan(h) && !isnan(t)) {
            m_temperature = (int)t;
            m_humidity = (int)h;

          if (m_page == ENV) {
              display(); 
          }
        } else {
            Serial.println("Blad odczytu z DHT11!");
        }
    }

void HMIPanel::drawProgressBar(int value, int minValue, int maxValue, int row, int maxChars) {
  value = constrain(value, minValue, maxValue);
  
  int percentage = map(value, minValue, maxValue, 0, 100);
  
  int totalPixelColumns = map(percentage, 0, 100, 0, maxChars * 5);
  
  m_lcd->setCursor(0, row);
  
  for (int i = 0; i < maxChars; i++) {
    if (totalPixelColumns >= 5) {
      m_lcd->write(5); 
      totalPixelColumns -= 5;
    } else if (totalPixelColumns > 0) {
      m_lcd->write(totalPixelColumns); 
      totalPixelColumns = 0;
    } else {
      m_lcd->write(' '); 
    }
  }
}