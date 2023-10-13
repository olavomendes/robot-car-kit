#include <SR04.h>
#include <Servo.h>

#define triggerPin A1
#define echoPin A0
#define speedPinA 5
#define speedPinB 6

SR04 ultrasonicSensor = SR04(echoPin, triggerPin);
long rightObstacleDistance = 0;
long obstacleDistance = 0;
long leftObstacleDistance = 0;

Servo servo;
int servoPosition = 0;

int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;

int motorSpeed = 40;

void carConfig() {
   for(int i=2; i< 9; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);

  servo.attach(A2);
  servo.write(90);
}

void motorsConfig() {
  digitalWrite(speedPinA, motorSpeed);
  digitalWrite(speedPinB, motorSpeed);
}

void goAdvance() {
  motorsConfig();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  stopMovement();
}

void goBack() {
  motorsConfig();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void goLeft() {
  motorsConfig();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(300);
  stopMovement();
}

void goRight() {
  motorsConfig();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  stopMovement();
}

void stopMovement() {
  digitalWrite(speedPinA, 0);
  digitalWrite(speedPinB, 0);
}

int measureObstacleDistance() {
  obstacleDistance = ultrasonicSensor.Distance();
  return obstacleDistance;
}

void analyseField() {
  stopMovement();
  delay(500);

  goBack();
  delay(500);

  stopMovement();
  delay(1000);

  servo.write(0);
  rightObstacleDistance = measureObstacleDistance();
  delay(500);

  servo.write(180);
  leftObstacleDistance = measureObstacleDistance();
  delay(500);

  return rightObstacleDistance, leftObstacleDistance;
}

void avoidObstacles() {
  servo.write(90);
  goAdvance();
  obstacleDistance = measureObstacleDistance();

  if (obstacleDistance <= 30) {
    analyseField();

    if (rightObstacleDistance < leftObstacleDistance) {
      goLeft();
      delay(1000);
      stopMovement();
    } else {
      goRight();
      delay(1000);
      stopMovement();
    }
    
  }
}

void setup() {
  carConfig();
  stopMovement();
}

void loop() {
  avoidObstacles();
}
