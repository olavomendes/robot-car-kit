#include <Servo.h>

Servo myServo;
int servoPosition = 0; 

void setup() {
  myServo.attach(A2);
}

void loop() {
  for (servoPosition; servoPosition<=180; servoPosition++) {
    myServo.write(servoPosition);
    delay(15);
  }
  for (servoPosition=180; servoPosition>=0; servoPosition--) {
    myServo.write(servoPosition);
    delay(15);
  }
}
