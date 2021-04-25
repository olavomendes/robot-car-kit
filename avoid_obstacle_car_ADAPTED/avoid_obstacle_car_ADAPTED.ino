#include <Servo.h>
#include <SR04.h>
// PINOS DO SENSOR ULTRASSONICO
#define TRIG_PIN A1
#define ECHO_PIN A0
// PINOS DE VELOCIDADE DOS MOTORES
#define velPinA 5
#define velPinB 6

SR04 ultSensor = SR04(ECHO_PIN, TRIG_PIN); // SENSOR ULTRASSONICO
long distance; // DISTÂNCIA FRONTAL
long rightDistance; // DISTÂNCIA DO LADO DIREITO
long leftDistance; // DISTÂNCIA DO LADO ESQUERDO

Servo myServo; // SERVO
int posit = 0; // POSIÇÃO DO SERVO

// PINOS DO CONTROLADOR DOS MOTORES
int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;

// VELOCIDADE DOS MOTORES
int velA = 70;
int velB = 70;
// CONTADOR
int i = 2;

void controlConfig() {
  for(i; i< 9; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600); // INICIA O SERIAL

  myServo.attach(A2); // ANEXA O SERVO AO PINO A2
  myServo.write(90); // DEIXA O SERVO ALINHADO "PRA FRENTE"
}

// FUNÇÃO PARA FAZER O CARRINHO AVANÇAR
void advance() {
  digitalWrite(velPinA, velA);
  digitalWrite(velPinB, velB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
// FUNÇÃO PARA FAZER O CARRINHO VOLTAR
void back() {
  digitalWrite(velPinA, 50);
  digitalWrite(velPinB, 50);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
// FUNÇÃO PARA FAZER O CARRINHO PARAR
void stopp() {
  digitalWrite(velPinA, 0);
  digitalWrite(velPinB, 0);
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, HIGH);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, HIGH);
}
// FUNÇÃO PARA FAZER O CARRINHO IR PARA A ESQUERDA
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
// FUNÇÃO PARA FAZER O CARRINHO IR PARA A DIREITA
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

// FUNÇÃO QUE MEDE A DISTÂNCIA DO SENSOR ULTRASSONICO ATÉ UM OBSTÁCULO
int measureDistance() {
  distance = ultSensor.Distance();
  // Serial.print(distance);
  // Serial.println(" cm");
  // delay(500);
  return distance;
}

// >>>> FUNÇÃO APENAS PARA TESTAR O FUNCIONAMENTO DO SERVO
// void servo() {
//   for (posit; posit <= 180; posit++) {
//     myServo.write(posit);
//     delay(15);
//   }
//   for (posit = 180; posit >= 0; posit--) {
//     myServo.write(posit);
//     delay(15);
//   }
// }

void setup() {
  controlConfig();
  stopp();  
}

void loop() {

  myServo.write(90);
  advance(); // O CARRINHO AVANÇA
  distance = measureDistance(); // A DISTÂNCIA FRONTAL É MEDIDA
  

  // SE TIVER UM OBSTÁCULO À 15 CM OU MENOS DE DISTÂNCIA
  if (distance <= 15) {
    stopp(); // O CARRINHO PARA
    delay(500);
    back(); // VOLTA
    delay(500);
    stopp(); // PARA
    delay(1000);
    
    myServo.write(0); // O CARRINHO "OLHA" PARA A DIREITA
    rightDistance = measureDistance(); // MEDE A DISTÂNCIA

    delay(500);
    
    myServo.write(180); // O CARRINHO "OLHA" PARA A ESQUERDA
    leftDistance = measureDistance(); // MEDE A DISTÂNCIA
    
    delay(500);
    
    // SE A DISTÂNCIA DA DIREITA FOR MENOR QUE A ESQUERDA
    if (rightDistance < leftDistance) {
      left(); // O CARRINHO VIRA PARA A ESQUERDA
      delay(1000);
      stopp(); // PARA
    }else{
      // SE NÃO
      if (rightDistance > leftDistance) {
        right(); // O CARRINHO VIRA PARA A DIREITA
        delay(1000);
        stopp(); // PARA
      }
    }
  }
  // APÓS ISSO, O CARRINHO AVANÇA

  // >>>> CÓDIGO APENAS PARA TESTAR O SENSOR ULTRASSONICO
  // servo();
  // Serial.print(distance);
  // Serial.println(" cm");
  // delay(500);
}
