#include "Arduino.h"

namespace {
  constexpr uint8_t
    led_hi = 8, // Drive-controlled LED
    led_lo = 9, // Sink-controlled LED
    led_bd = 13;
}

void setup() {
  pinMode(led_hi, OUTPUT);
  pinMode(led_lo, OUTPUT);
  pinMode(led_bd, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  const auto meter = analogRead(A0);
  const bool hi = meter >> 9, lo = meter >> 8 & 1;

  digitalWrite(led_hi, hi ? HIGH : LOW);
  digitalWrite(led_lo, !lo ? HIGH : LOW);
  digitalWrite(led_bd, lo ? HIGH : LOW);
  Serial.print('(');
  Serial.print(hi);
  Serial.print(", ");
  Serial.print(lo);
  Serial.println(')');
  delay(20);
}
