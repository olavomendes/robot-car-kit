#include <Servo.h>
#include <SR04.h>
#include <IRremote.h>
#define IR_GO 0x00ff629d
#define IR_BACK 0x00ffa857
#define IR_LEFT 0x00ff22dd
#define IR_RIGHT 0x00ffc23d
#define IR_STOP 0x00ff02fd
#define MODE_IR 0x00ff6897
#define MODE_AUTO 0x00ff9867
#define velPinA 5
#define velPinB 6
#define TRIG_PIN A1
#define ECHO_PIN A0

SR04 ultSensor = SR04(ECHO_PIN, TRIG_PIN);
long distance;
long rightDistance;
long leftDistance;

Servo myServo;
int posit = 0;

int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results ir_car_results;
decode_results mode_results;

int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;

int velA = 150;
int velB = 150;
int i = 2;

// int mode;

void controlConfig() {
  for(i; i< 9; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  irrecv.enableIRIn();
}

int measureDistance() {
  distance = ultSensor.Distance();
  // Serial.print(distance);
  // Serial.println(" cm");
  // delay(500);
  return distance;
}

void advance() {
  digitalWrite(velPinA, velA);
  digitalWrite(velPinB, velB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void back() {
  digitalWrite(velPinA, 50);
  digitalWrite(velPinB, 50);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void left() {
  digitalWrite(velPinA, 50);
  digitalWrite(velPinB, 50);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(300);
  stopp();
}
void right() {
  digitalWrite(velPinA, 50);
  digitalWrite(velPinB, 50);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  stopp();
}
void stopp() {
  digitalWrite(velPinA, 0);
  digitalWrite(velPinB, 0);
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, HIGH);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, HIGH);
}

void IRControl(void) {
  unsigned long button;

  if (irrecv.decode(&ir_car_results)) {
    button = ir_car_results.value;

    switch(button) {
      case IR_GO: advance(); break;
      case IR_BACK: back(); break;
      case IR_RIGHT: right(); break;
      case IR_LEFT: left(); break;
      case IR_STOP: stopp(); break;
      default: break;
      
    }
    irrecv.resume();
  }
}

void autoControl() {
  
  myServo.write(90);
  advance();
  distance = measureDistance();
  

  if (distance <= 15) {
    stopp();
    delay(500);
    back();
    delay(500);
    stopp();
    delay(1000);
    
    myServo.write(0); // direita
    rightDistance = measureDistance();

    delay(500);
    
    myServo.write(180); // esquerda
    leftDistance = measureDistance();
    
    delay(500);
    
    if (rightDistance < leftDistance) {
      left();
      delay(1000);
      stopp();
    }else{
      if (rightDistance > leftDistance) {
        right();
        delay(1000);
        stopp();
      }
    }
  }
}

int carMode() {
  unsigned long modeButton;
  int mode;

  if (irrecv.decode(&mode_results)) {
    modeButton = mode_results.value;
  
    switch(modeButton) {
      case MODE_IR: mode = 1; break;
      case MODE_AUTO: mode = 2; break;
      default: break;
    }
    irrecv.resume();
  }
  return mode;
}

void setup() {
  controlConfig();
  stopp();
}

void loop() {

  int mode = carMode();
  Serial.println(mode);
  delay(1000);

  if(mode == 1) {
    IRControl();
  }else{
    if(mode == 2){
      autoControl();
    }
  }
}
