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
public:
    HMIPanel(hmi_page page_mode, LiquidCrystal* lcd);
    ~HMIPanel();
    void display();
    void nextPage();

    void setTemperature(int temperature) { m_temperature = temperature; }
    void setLightsLevel(int lights_level) { m_lights_level = lights_level; }
    void setHumidity(int humidity) { m_humidity = humidity; }

    int getTemperature() const { return m_temperature; }
    int getHumidity() const    { return m_humidity; }
    int getLightsLevel() const { return m_lights_level; }
    hmi_page getPage() const { return m_page; }
};
