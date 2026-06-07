#include <Arduino.h>
#include "HMIPanel.h"

HMIPanel::HMIPanel(hmi_page page_mode, LiquidCrystal* lcd, int switch_pin) 
    : m_page(page_mode), m_lcd(lcd), m_lights_level(0), 
      m_temperature(0), m_humidity(0), m_switch_pin(switch_pin) 
{}

HMIPanel::~HMIPanel() {}

void HMIPanel::display() {
    m_lcd->clear();
    switch (m_page) {
        case LIGHTS:
            m_lcd->setCursor(0, 0);
            m_lcd->print("Lights level: ");
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

void HMIPanel::setTemperature(int temperature) { m_temperature = temperature; }
void HMIPanel::setLightsLevel(int lights_level) { m_lights_level = lights_level; }
void HMIPanel::setHumidity(int humidity) { m_humidity = humidity; }

int HMIPanel::getTemperature() const { return m_temperature; }
int HMIPanel::getHumidity() const    { return m_humidity; }
int HMIPanel::getLightsLevel() const { return m_lights_level; }