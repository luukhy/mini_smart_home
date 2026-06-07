#pragma once
#include <Arduino.h>

class Button {
private:
    int m_pin;
    int m_button_state;
    int m_last_button_state;
    unsigned long m_last_debounce_time;
    unsigned long m_debounce_delay;
    unsigned long m_window_time;
    int m_click_count;
    unsigned long m_last_click_time;

public:
    Button(int pin, unsigned long debounceDelay = 50, unsigned long windowTime = 450);
    
    void init();

    int isPressed();
    
    int checkClicks(); 
};