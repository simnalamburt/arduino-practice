#include "util.hh"
#include "mode.hh"
#include "animator.hh"
#include "analog_button.hh"
#include "potentiometer.hh"
#include "Arduino.h"

namespace {
  Mode<4> mode;
  Animator anime;

  // Digital pin numbers of connected LEDs
  constexpr uint8_t LEDs[] { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

  // Input hardwares
  Potentiometer<A0> meter;
  AnalogButton<A1> left;
  AnalogButton<A2> right;
}

void setup() {
  for (const auto led: LEDs) { pinMode(led, OUTPUT); }

  Serial.begin(9600);
}

void loop() {
  using util::length;
  using util::range;

  // Need to be called once a every loop
  anime.onLoop();
  left.onLoop();
  right.onLoop();


  // Update mode
  if (left.clicked()) { --mode; }
  if (right.clicked()) { ++mode; }

  // Use the value of potentiometer as a speed of the animation. The speed will
  // be a double ∈ [0.3, 1.5)
  anime.speed = 1.2 * meter.get() + 0.3;

  // Turn off all LEDs on mode 0
  switch (mode) {
  case 0: {
    // 회전화면서 빛이 켜짐
    constexpr auto len = length(LEDs);
    const auto idx_ = size_t(anime.pos * Animator::type(len));
    const auto idx = idx_ >= len ? len : idx_; // Prevent memory error

    // TODO: Remove debug codes
    Serial.print("Index: ");
    Serial.print(idx);
    Serial.print(" \t");

    for (const auto i: range(0u, idx)) { digitalWrite(LEDs[i], LOW); }
    digitalWrite(LEDs[idx], HIGH);
    for (const auto i: range(idx + 1, len)) { digitalWrite(LEDs[i], LOW); }
    break; }
  case 1:
    // 하트가 깜빡깜빡거림
    for (const auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 2:
    // 전부 끔
    for (const auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 3:
    // 전부 켬
    for (const auto led: LEDs) { digitalWrite(led, HIGH); }
    break;
  }

  // TODO: Remove debug codes
  Serial.print("Period: ");
  Serial.print(anime.period);
  Serial.print(" \tMode: ");
  Serial.print(mode);
  Serial.print(" \tPos: ");
  Serial.println(anime.pos);
}
