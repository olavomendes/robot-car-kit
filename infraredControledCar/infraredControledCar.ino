#include <IRremote.h>
#define IR_GO_BUTTON 0x00ff629d
#define IR_BACK_BUTTON 0x00ffa857
#define IR_LEFT_BUTTON 0x00ff22dd
#define IR_RIGHT_BUTTON 0x00ffc23d
#define IR_STOP_BUTTON 0x00ff02fd

#define velocityPinA 5
#define velocityPinB 6

int receiverPin = 12;
IRrecv irrecv(receiverPin);
decode_results receiverResults;

int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;

int quarterVelocity = 64;
int halfVelocity = 128; 
int fullVelocity = 255; 

void controlConfig() {
  for(int i=2; i<=8; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600); 
  irrecv.enableIRIn();
}

void goAdvance() {
  digitalWrite(velocityPinA, quarterVelocity);
  digitalWrite(velocityPinB, quarterVelocity);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void goBack() {
  digitalWrite(velocityPinA, quarterVelocity);
  digitalWrite(velocityPinB, quarterVelocity);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void goLeft() {
  digitalWrite(velocityPinA, quarterVelocity);
  digitalWrite(velocityPinB, quarterVelocity);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(300);
  stopMoviment();
}

void goRight() {
  digitalWrite(velocityPinA, quarterVelocity);
  digitalWrite(velocityPinB, quarterVelocity);
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

void IRControl(void) {
  unsigned long pressedButton; 

  if (irrecv.decode(&receiverResults)) {
    pressedButton = receiverResults.value;

    switch(pressedButton) {
      case IR_GO_BUTTON: goAdvance(); break;
      case IR_BACK_BUTTON: goBack(); break;
      case IR_RIGHT_BUTTON: goRight(); break;
      case IR_LEFT_BUTTON: goLeft(); break;
      case IR_STOP_BUTTON: stopMoviment(); break;
      default: break;
      
    }
    irrecv.resume(); 
  }
}

void setup() {
  controlConfig(); 
  stopMoviment(); 
}

void loop() {
  IRControl(); 
}
