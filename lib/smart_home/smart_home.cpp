#include <Arduino.h>

int debounce(int pin, int &buttonState, int &lastButtonState, unsigned long &lastDebounceTime, unsigned long debounceDelay ) {

  int reading = digitalRead(pin);
  if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        // Serial.println("Przycisk wciśnięty");
        return 1;
      }
    }
  }
  lastButtonState = reading;
  return 0;
}