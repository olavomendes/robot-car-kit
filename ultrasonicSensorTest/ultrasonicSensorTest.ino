#include "SR04.h"

#define TRIGGER_PIN A1
#define ECHO_PIN A0

SR04 ultrasonicSensor = SR04(ECHO_PIN, TRIGGER_PIN);
long distance = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  distance = ultrasonicSensor.Distance();
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}
