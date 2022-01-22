#include <SR04.h>
#include <Servo.h>

#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define velocityPinA 5
#define velocityPinB 6

SR04 ultrasonicSensor = SR04(ECHO_PIN, TRIGGER_PIN); 
long obstracleDistance; 
long obstracleRightDistance; 
long obstracleLeftDistance; 

Servo myServo; 
int myServoPosition = 0;

int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;

int motorVelocity = 40;

void controlConfig() {
  for(int i=2; i< 9; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600); 
  myServo.attach(A2);
  myServo.write(90);
}

void goAdvance() {
  digitalWrite(velocityPinA, motorVelocity);
  digitalWrite(velocityPinB, motorVelocity);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void goBack() {
  digitalWrite(velocityPinA, motorVelocity);
  digitalWrite(velocityPinB, motorVelocity);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void goLeft() {
  digitalWrite(velocityPinA, motorVelocity);
  digitalWrite(velocityPinB, motorVelocity);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(300);
  stopMoviment();
}

void goRight() {
  digitalWrite(velocityPinA, motorVelocity);
  digitalWrite(velocityPinB, motorVelocity);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  stopMoviment();
}

void stopMoviment() {
  digitalWrite(velocityPinA, 0);
  digitalWrite(velocityPinB, 0);
}

int measureDistance() {
  obstracleDistance = ultrasonicSensor.Distance();
  return obstracleDistance;
}

void avoidObstacle() {
  myServo.write(90);
  goAdvance(); 
  obstracleDistance = measureDistance(); 
  

  if (obstracleDistance <= 15) {
    stopMoviment(); 
    delay(500);
    goBack(); 
    delay(500);
    stopMoviment(); 
    delay(1000);
    
    myServo.write(0); 
    obstracleRightDistance = measureDistance();

    delay(500);
    
    myServo.write(180); 
    obstracleLeftDistance = measureDistance(); 
    
    delay(500);
    
    if (obstracleRightDistance < obstracleLeftDistance) {
      goLeft();
      delay(1000);
      stopMoviment();
      
    } else {
       goRight(); 
       delay(1000);
       stopMoviment();  
    }
  }
}

void setup() {
  controlConfig();
  stopMoviment();  
}

void loop() {
  avoidObstacle();
}
