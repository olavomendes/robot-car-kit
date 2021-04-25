#include <IRremote.h>
// CÓDIGOS DOS BOTÕES DO CONTROLE IR
#define IR_GO 0x00ff629d
#define IR_BACK 0x00ffa857
#define IR_LEFT 0x00ff22dd
#define IR_RIGHT 0x00ffc23d
#define IR_STOP 0x00ff02fd
// VELOCIDADE DOS MOTORES
#define velPinA 5
#define velPinB 6

// CONFIGURAÇÕES DO RECEPTOR IR
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

// PINOS CONECTADOS NO CONTROLADOR DO MOTOR
int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;

// VELOCIDADE DOS MOTORES
int velA = 100;
int velB = 100;
int i = 2; // CONTADOR

// CONFIGURAÇÕES  INICIAIS
void controlConfig() {
  for(i; i< 9; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600); // INICIA O SERIAL
  irrecv.enableIRIn(); // HABILITA O RECEPTOR IR
}

// COMANDO PARA O CARRINHO AVANÇAR
void advance() {
  digitalWrite(velPinA, velA);
  digitalWrite(velPinB, velB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
// COMANDO PARA O CARRINHO VOLTAR
void back() {
  digitalWrite(velPinA, 50);
  digitalWrite(velPinB, 50);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
// COMANDO PARA O CARRINHO IR PARA A ESQUERDA
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
// COMANDO PARA O CARRINHO IR PARA A DIREITA
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
// COMANDO PARA O CARRINHO PARAR
void stopp() {
  digitalWrite(velPinA, 0);
  digitalWrite(velPinB, 0);
  // ABAIXO, HÁ UMA ALTERNATIVA DE COMENDOS PARA PARAR O CARRINHO

  // digitalWrite(IN1, HIGH);
  // digitalWrite(IN2, HIGH);
  // digitalWrite(IN3, HIGH);
  // digitalWrite(IN4, HIGH);
}

// CONTROLE DO CARRINHO ATRAVÉS DE IR
void IRControl(void) {
  unsigned long button; // ARMAZENA O BOTÃO PRESSIONADO

  if (irrecv.decode(&results)) {
    button = results.value; // ARMAZENA O BOTÃO PRESSIONADO

    // CHAMA A FUNÇÃO QUE MOVE O CARRINHO DE ACORDO COM O BOTÃO PRESSIONADO
    switch(button) {
      case IR_GO: advance(); break;
      case IR_BACK: back(); break;
      case IR_RIGHT: right(); break;
      case IR_LEFT: left(); break;
      case IR_STOP: stopp(); break;
      default: break;
      
    }
    irrecv.resume(); // O SENSOR IR RECEBE NOVOS VALORES
  }
}

void setup() {
  controlConfig(); 
  stopp(); // O CARRINHO INICIA PARADO
}

void loop() {
  IRControl(); // CHAMA A FUNÇÃO PARA CONTROLAR O CARRINHO
}