#include "Button.h"

Button::Button(int pin, unsigned long debounceDelay, unsigned long windowTime)
    : m_pin(pin), m_button_state(LOW), m_last_button_state(LOW), 
      m_last_debounce_time(0), m_debounce_delay(debounceDelay), 
      m_window_time(windowTime), m_click_count(0), m_last_click_time(0) {}

void Button::init() {
    pinMode(m_pin, INPUT_PULLDOWN);
}

int Button::isPressed() {
    int reading = digitalRead(m_pin);
    unsigned long currentTime = millis();

    if (reading != m_last_button_state) {
        m_last_debounce_time = currentTime;
    }

    if ((currentTime - m_last_debounce_time) > m_debounce_delay) {
        if (reading != m_button_state) {
            m_button_state = reading;

            if (m_button_state == HIGH) {
                m_last_click_time = currentTime;
                return 1;
            }
        }
    }

    m_last_button_state = reading;
    return 0;
}

int Button::checkClicks() {
    int reading = digitalRead(m_pin);
    unsigned long currentTime = millis();
    int action = 0; 

    if (isPressed()) {
        m_click_count++;
        m_last_click_time = currentTime;
    }

    if (m_click_count > 0 && (currentTime - m_last_click_time) > m_window_time) {
        action = m_click_count; 
        m_click_count = 0;    
    }

    return action;
}