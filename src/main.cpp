#include "Arduino.h"

namespace {
  constexpr uint8_t button = 2, led = 13;
  int counter = 0;
  bool buttonState = false;
}

void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  auto newState = digitalRead(button) != 0;
  if (!buttonState && newState) { ++counter; }
  buttonState = newState;

  // Output
  digitalWrite(led, newState ? HIGH : LOW);
  Serial.println(counter);

  delay(20);
}
