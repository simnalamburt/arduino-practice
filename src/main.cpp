#include "mode.hh"
#include "analog_button.hh"
#include "potentiometer.hh"
#include "Arduino.h"

namespace {
  // Digital pin numbers of connected LEDs
  constexpr uint8_t LEDs[] { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

  // Internal state of this program
  Mode<4> mode;

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
  left.onLoop();
  right.onLoop();

  // Update mode
  if (left.clicked()) { mode.dec(); }
  if (right.clicked()) { mode.inc(); }

  // Get the value of potentiometer
  const auto vel = meter.read();

  // Turn off all LEDs on mode 0
  switch (mode) {
  case 1:
    // TODO: 회전화면서 빛이 켜짐. 포텐시오미터로 속도를 조절함
    for (auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 2:
    // TODO: 하트가 깜빡깜빡거림. 포텐시오미터로 속도를 조절함
    for (auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 3:
    // 전부 끔
    for (auto led: LEDs) { digitalWrite(led, LOW); }
    break;
  case 4:
    // 전부 켬
    for (auto led: LEDs) { digitalWrite(led, HIGH); }
    break;
  }

  // Debug purpose
  Serial.print("Potentiometer: ");
  Serial.print(vel);
  Serial.print(" \tMode: ");
  Serial.println(mode);

  // Framerate
  delay(20);
}
