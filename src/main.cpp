#include "Arduino.h"

constexpr uint8_t button = 2, led = 13;

void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  auto val = digitalRead(button);
  digitalWrite(led, val ? HIGH : LOW);
  Serial.println(val);
  delay(20);
}
