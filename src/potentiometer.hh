#pragma once
#include "Arduino.h"

//
// Wrapper for a potentiometer. It normalize its input from integral number
// between [0, 1024) to floating point number between [0.0f, 1.0f)
//
template<uint8_t pin>
struct Potentiometer {
  float read() const {
    const auto raw = analogRead(pin);
    return float(raw) / 1024.0f;
  }
};
