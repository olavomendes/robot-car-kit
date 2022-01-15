#include "SR04.h"

#define TRIG_PIN A1
#define ECHO_PIN A0

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long distance = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  distance = sr04.Distance();
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}
