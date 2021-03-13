#include <IRremote.h>
#define IR_GO 0x00ff629d
#define IR_BACK 0x00ffa857
#define IR_LEFT 0x00ff22dd
#define IR_RIGHT 0x00ffc23d
#define IR_STOP 0x00ff02fd
#define IR_ESC 0x00ff52ad
#define L_PWM_PIN 5 // PINO DA VELOCIDADE DAS RODAS DA ESQUERDA
#define R_PWM_PIN 6 // PINO DA VELOCIDADE DAS RODAS DA DIREITA

// TAMBÉM PODEM SER CHAMADOS DE IN1, IN2, IN3 e IN4
int pinLB = 2; // RODA TRASEIRO ESQUERDA
int pinLF = 4; // RODA FRONTAL ESQUERDA
int pinRB = 7; // RODA TRASEIRO DIREITA
int pinRF = 8; // RODA FRONTAL DIREITA

unsigned char L_PWM_VAL = 150; // VALOR DA VELOCIDADE
unsigned char R_PWM_VAL = 150;
int carState = 0;

int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

void controlConfig(void) {
  pinMode(pinLB,OUTPUT); 
  pinMode(pinLF,OUTPUT); 
  pinMode(pinRB,OUTPUT); 
  pinMode(pinRF,OUTPUT);
  pinMode(L_PWM_PIN, OUTPUT);
  pinMode(R_PWM_PIN, OUTPUT);
}

void setSpeed(unsigned char left, unsigned char right) {
  analogWrite(L_PWM_PIN, left);
  analogWrite(R_PWM_PIN, right);
}

void advance() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
  carState = 1;
}

void turnRight() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
  carState = 4;
}

void turnLeft() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
  carState = 3;
}

void back() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
  carState = 2;  
}

void stop() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, HIGH);
  carState = 5;
}

void IRControl(void) {
  unsigned long key;

  if (irrecv.decode(&results)) {
    key = results.value;

    switch(key) {
      case IR_GO: advance(); break;
      case IR_BACK: back(); break;
      case IR_LEFT: turnLeft(); break;
      case IR_RIGHT: turnRight(); break;
      case IR_STOP: stop(); break;
      default: 
      break;
    }
    irrecv.resume(); // RECEBE O PRÓXIMO VALOR
  }
}

void setup() {
  controlConfig();
  setSpeed(L_PWM_VAL, R_PWM_VAL);
  irrecv.enableIRIn();
  Serial.begin(9600);
  stop();
}

void loop() {
  IRControl();
}
