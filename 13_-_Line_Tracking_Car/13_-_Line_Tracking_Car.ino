#define sensorLeft 9
#define sensorMiddle 10
#define sensorRight 11
#define l_pwm_pin 5
#define r_pwm_pin 6

unsigned char SL; // state of sensor
unsigned char SM;
unsigned char SR;

int pinLB = 2;
int pinLF = 4;
int pinRB = 7;
int pinRF = 8;

unsigned char l_pwm_val = 120;
unsigned char r_pwm_val = 120;

int car_state = 0;

void sensorConfig() {
  pinMode(sensorLeft, INPUT);
  pinMode(sensorMiddle, INPUT);
  pinMode(sensorRight, INPUT);
}

void sensorScan() {
  SL = digitalRead(sensorLeft);
  SM = digitalRead(sensorMiddle);
  SR = digitalRead(sensorRight);
}

void controlConfig(){
  pinMode(pinLB,OUTPUT); // pin 2--IN1 of motor driver board
  pinMode(pinLF,OUTPUT); // pin 4--IN2 of motor driver board
  pinMode(pinRB,OUTPUT); // pin 7--IN3 of motor driver board
  pinMode(pinRF,OUTPUT); // pin 8--IN4 of motor driver board
  pinMode(l_pwm_pin,OUTPUT); // pin 5  (PWM) --ENA of motor driver board
  pinMode(r_pwm_pin,OUTPUT);
}

void setSpeed(unsigned char left, unsigned char right) {
  analogWrite(l_pwm_pin, left);
  analogWrite(r_pwm_pin, right);
}

void advance() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
  car_state = 1;
}

void turnRight() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
  car_state = 4;
}

void turnLeft() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
  car_state = 3;
}

void stopp() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, HIGH);
  car_state = 5;
}

void back() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
  car_state = 2;
}

void setup() {
  sensorConfig();
  controlConfig();
  setSpeed(l_pwm_val, r_pwm_val);
  stopp();
  unsigned char oldSL, oldSM, oldSR;
}

void loop() {
  sensorScan();

  if (SM == HIGH) {
    if (SL == LOW & SR == HIGH){
      turnRight();
  }else if (SR == LOW & SL == HIGH) {
    turnLeft();
  } else {
    advance();
    }
  } else {
    if (SL == LOW & SL == HIGH) {
      turnLeft();
    }else {
      back();
      delay(100);
      stopp();
    }
  }
} // final
