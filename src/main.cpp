#include "Arduino.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  // print labels
  Serial.println("NO FMT\tDEC\tHEX\tOCT\tBIN");

  for (auto x = 0; x < 64; ++x) {
    Serial.print(x);
    Serial.print("\t");

    Serial.print(x, DEC);
    Serial.print("\t");

    Serial.print(x, HEX);
    Serial.print("\t");

    Serial.print(x, OCT);
    Serial.print("\t");

    Serial.println(x, BIN);

    delay(200);
  }
  Serial.println("");
}
