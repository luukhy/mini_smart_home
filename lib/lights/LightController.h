#pragma once
#include <Arduino.h>

class LightController {
private:
    int m_pin;
    bool m_state;
    int m_duty_cycle;

public:
    LightController(int pin);
    
    void init();
    
    void toggle();
    
    void setBrightness(int pwmValue);
    
    int getBrightness();
};