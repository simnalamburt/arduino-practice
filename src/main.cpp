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

  // 모드별로 동작이 다르다
  //
  // 0:  하트 가장자리를 따라 LED가 빙글빙글 돌면서 켜진다.
  // 1:  하트가 두근두근거리면서 켜진다.
  // 2:  하트가 켜져있는채로 유지된다.
  // 3:  하트가 꺼진다.
  switch (mode) {
  case 0: {
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
  case 1: {
    const auto pos = anime.pos;
    const auto state = 0.0 <= pos && pos < 0.15 || 0.25 <= pos && pos < 0.33 ? HIGH : LOW;
    for (const auto led: LEDs) { digitalWrite(led, state); }
    break; }
  case 2:
    for (const auto led: LEDs) { digitalWrite(led, HIGH); }
    break;
  case 3:
    for (const auto led: LEDs) { digitalWrite(led, LOW); }
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
