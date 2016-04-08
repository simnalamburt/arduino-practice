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
  for (auto led: LEDs) { pinMode(led, OUTPUT); }

  Serial.begin(9600);
}

void loop() {
  // Need to be called once a every loop
  anime.onLoop();
  left.onLoop();
  right.onLoop();


  // Update mode
  if (left.clicked()) { --mode; }
  if (right.clicked()) { ++mode; }

  // Use the value of potentiometer as a period of the animation
  // The period will be a double ∈ [0.3, 1.5)
  anime.speed = 1.2 * meter.get() + 0.3;

  // Turn off all LEDs on mode 0
  switch (mode) {
  case 0:
    // TODO: 회전화면서 빛이 켜짐. 포텐시오미터로 속도를 조절함
    for (auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 1:
    // TODO: 하트가 깜빡깜빡거림. 포텐시오미터로 속도를 조절함
    for (auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 2:
    // 전부 끔
    for (auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 3:
    // 전부 켬
    for (auto led: LEDs) { digitalWrite(led, HIGH); }
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
