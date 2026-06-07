#include <Arduino.h>
#include <LiquidCrystal.h>

int debounce(int pin, int &buttonState, int &lastButtonState, unsigned long &lastDebounceTime, unsigned long debounceDelay ) {

  int reading = digitalRead(pin);
  if (reading != lastButtonState) {
      lastDebounceTime = millis(); // Zapisz czas zmiany stanu przycisku
    }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Stan przycisku się ustalił
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        Serial.println("Przycisk wciśnięty");
        return 1;
      }
    }
  }
  lastButtonState = reading; // Zapisz aktualny stan przycisku
  return 0;
}