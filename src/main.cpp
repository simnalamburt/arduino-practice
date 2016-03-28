#include "Arduino.h"

namespace {
  constexpr uint8_t led = 13;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));
  delay(20);
}
