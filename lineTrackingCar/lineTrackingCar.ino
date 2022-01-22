#define leftSensor 9
#define middleSensor 10
#define rightSensor 11
#define velocityPinA 5
#define velocityPinB 6

unsigned char leftSensorState;
unsigned char middleSensorState;
unsigned char rightSensorState;

int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;

unsigned char leftMotorVelocity = 120;
unsigned char rightMotorVelocity = 120;

int car_state = 0;

void sensorConfig() {
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
}

void sensorScanner() {
  leftSensorState = digitalRead(leftSensor);
  middleSensorState = digitalRead(middleSensor);
  rightSensorState = digitalRead(rightSensor);
}

void controlConfig() {
  for(int i=2; i<=8; i++){
    pinMode(i, OUTPUT);
  }
}

void setMotorVelocity(unsigned char leftVelocity, unsigned char rightVelocity) {
  analogWrite(leftMotorVelocity, leftVelocity);
  analogWrite(rightMotorVelocity, rightVelocity);
}

void goAdvance() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void goBack() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void goLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(300);
  stopMoviment();
}

void goRight() {
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

void setup() {
  sensorConfig();
  controlConfig();
  setMotorVelocity(leftMotorVelocity, rightMotorVelocity);
  stopMoviment();
  unsigned char oldLeftSensorState, oldMiddleSensorState, oldRightSensorState;
}

void loop() {
  sensorScanner();

  if (middleSensorState == HIGH) {
    if (leftSensorState == LOW & rightSensorState == HIGH){
      goRight();
      
  }else if (rightSensorState == LOW & leftSensorState == HIGH) {
    goLeft();
  } else {
    goAdvance();
    }
    
  } else {
    if (leftSensorState == LOW & rightSensorState == HIGH) {
      goRight();
      
    }else if (rightSensorState == LOW & leftSensorState == HIGH) {
      goLeft();
      
    } else {
      goBack();
      delay(100);
      stopMoviment();
    }
  }
}
