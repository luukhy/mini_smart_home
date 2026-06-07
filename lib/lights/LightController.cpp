#include "LightController.h"

LightController::LightController(int pin) : m_pin(pin), m_state(false), m_duty_cycle(126) {}

void LightController::init() {
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW); 
}

void LightController::toggle() {
    m_state = !m_state;
    analogWrite(m_pin, m_state ? m_duty_cycle : 0);
}

void LightController::setBrightness(int pwmValue) {
    m_duty_cycle += pwmValue;
    if (m_duty_cycle > 255) m_duty_cycle = 255;
    if (m_duty_cycle < 50) m_duty_cycle = 50;
    
    analogWrite(m_pin, m_duty_cycle);
}