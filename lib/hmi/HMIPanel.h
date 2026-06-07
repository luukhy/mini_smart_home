// HMIPanel.h

#pragma once

#include <LiquidCrystal.h>

enum hmi_page{
    LIGHTS = 0,
    ENV,
    NUM_PAGES
};

class HMIPanel
{
private:
    hmi_page m_page;
    LiquidCrystal* m_lcd;
    
    int m_lights_level;
    int m_temperature;
    int m_humidity;
    int m_switch_pin;
public:
    HMIPanel(hmi_page page_mode, LiquidCrystal* lcd, int switch_pin);
    ~HMIPanel();
    void display();
    void nextPage();

    void setLightsLevel(int lights_level);
    void setTemperature(int temperature);
    void setHumidity(int humidity);

    int getTemperature() const;
    int getHumidity() const;
    int getLightsLevel() const;
};
