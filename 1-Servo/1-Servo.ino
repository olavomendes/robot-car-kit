#include <Servo.h>

Servo myServo;
int position = 0;

void setup() {
  myServo.attach(A2);
}

void loop() {

  for (position; position<=180; position++) {
    myServo.write(position);
    delay(15);
  }
  for (position=180; position>=0; position--) {
    myServo.write(position);
    delay(15);
  }
}
