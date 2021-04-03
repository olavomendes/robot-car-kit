#include <Servo.h>

Servo myServo;
int pos = 0; // posição do servo

void setup() {
  myServo.attach(A2);
}

void loop() {

  for (pos; pos<=180; pos++) {
    myServo.write(pos);
    delay(15);
  }
  for (pos=180; pos>=0; pos--) {
    myServo.write(pos);
    delay(15);
  }
}
