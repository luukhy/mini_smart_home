// smart_home.h
#pragma once

int debounce(int pin, int &buttonState, int &lastButtonState, unsigned long &lastDebounceTime, unsigned long debounceDelay );