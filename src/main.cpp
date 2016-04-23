#include "util.hh"
#include "mode.hh"
#include "animator.hh"
#include "analog_button.hh"
#include "potentiometer.hh"
#include "Arduino.h"

namespace {
  constexpr uint8_t LEDs[] { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
  decltype(analogRead(A0)) v1_min = 1023, v1_max = 0, v2_min = 1024, v2_max = 0;
}

void setup() {
  for (const auto led: LEDs) { pinMode(led, OUTPUT); }

  Serial.begin(9600);
}

void loop() {
  const auto v1 = analogRead(A1);
  const auto v2 = analogRead(A2);

  if (v1 < v1_min) { v1_min = v1; }
  if (v1_max < v1) { v1_max = v1; }
  if (v2 < v2_min) { v2_min = v2; }
  if (v2_max < v2) { v2_max = v2; }

  const auto lit = v1 <= 600 ? HIGH : LOW;
  for (const auto led: LEDs) { digitalWrite(led, lit); }

  Serial.print("Pull Down: ");
  Serial.print(v1);
  Serial.print(" (");
  Serial.print(v1_min);
  Serial.print(", ");
  Serial.print(v1_max);
  Serial.print(")      Pull Up: ");
  Serial.print(v2);
  Serial.print(" (");
  Serial.print(v2_min);
  Serial.print(", ");
  Serial.print(v2_max);
  Serial.println(')');
  delay(50);
}
