#include "util.hh"
#include "potentiometer.hh"

namespace {
  Potentiometer<A0> meter;

  constexpr auto num = 50;
  auto idx = 0;

  decltype(meter.get()) reads[num] = {};
  decltype(meter.get()) total = 0.0;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  using util::length;
  using util::range;

  const auto val = meter.get();

  total = total - reads[idx] + val;
  reads[idx] = val;
  idx = idx == num - 1 ? 0 : idx + 1;

  Serial.print("Average: ");
  Serial.print(total / num);
  Serial.print("\t (current: ");
  Serial.print(val);
  Serial.println(")");
  delay(1);
}
