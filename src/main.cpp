#include <Arduino.h>
#include <LiquidCrystal.h>

#include "smart_home.h"

// const int RS = 13;
// const int EN = 14;
// const int D4 = 27;
// const int D5 = 26;
// const int D6 = 25;
// const int D7 = 33;
const int switchPin = 15;
const int buttonPin = 4;
const int ledPin = 16;
bool LEDState = false;
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int dutyCycle = 0;
int prevTime = 0;
int clicktime = 0;

// LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  Serial.begin(115200);
  Serial.println("Inicjalizacja SWAR");

  pinMode(switchPin, OUTPUT);
  digitalWrite(switchPin, HIGH); // Włącz pull-up
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Ustaw stan początkowy LED na wyłączony

}



void loop() {
  if (debounce(buttonPin, buttonState, lastButtonState, lastDebounceTime, debounceDelay) == 1) {
    LEDState = !LEDState; // Zmień stan LED
    digitalWrite(ledPin, LEDState); // Ustaw stan LED
}

  // prevTime = millis(); // Zapisz czas rozpoczęcia pętli
  // if (digitalRead(buttonPin) == HIGH) { // Przycisk jest wciśnięty
  //   if (prevTime - clicktime > 1000 or clicktime == 0) { // Sprawdź, czy czas między naciśnięciami jest krótszy niż 200 ms
  //      clicktime = prevTime; // Zapisz czas naciśnięcia}
  //      LEDState = !LEDState; // Zmień stan LED
  //      digitalWrite(ledPin, LEDState ? HIGH : LOW); // Ustaw stan LED
  //   } else {
  //      Serial.println("Przycisk wciśnięty, ale czas między naciśnięciami jest zbyt krótki.");
  //   }
    
  // }
 
}