#include <Arduino.h>

boolean power = false;

void writeToLed();
void toggleLedPower();

void initLed() {
  pinMode(LED_PIN, OUTPUT);
  writeToLed();
}

void toggleLedPower() {
  power = !power;
  writeToLed();
}

void writeToLed() {
  digitalWrite(LED_PIN, power ? HIGH : LOW);
}
