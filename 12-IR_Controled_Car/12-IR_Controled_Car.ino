#include <IRremote.h>
#define IR_GO 0x00ff629d // FRENTE
#define IR_BACK 0x00ffa857 // RÉ
#define IR_LEFT 0x00ff22dd // VIRAR À ESQUERDA
#define IR_RIGHT 0x00ffc23d // VIRAR _A DIREITA
#define IR_STOP 0x00ff02fd // PARAR
#define IR_ESC 0x00ff52ad 
#define L_PWM_PIN 5 // PINO DA VELOCIDADE DAS RODAS DA ESQUERDA
#define R_PWM_PIN 6 // PINO DA VELOCIDADE DAS RODAS DA DIREITA

// TAMBÉM PODEM SER CHAMADOS DE IN1, IN2, IN3 e IN4
int pinLB = 2; // RODA TRASEIRA ESQUERDA
int pinLF = 4; // RODA FRONTAL ESQUERDA
int pinRB = 7; // RODA TRASEIRA DIREITA
int pinRF = 8; // RODA FRONTAL DIREITA

unsigned char L_PWM_VAL = 150; // VALOR DA VELOCIDADE
unsigned char R_PWM_VAL = 150;
int carState = 0;

// CONFIGURAÇÕES DO IR
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

// FUNÇÃO DE DEFINIÇÃO DOS PINOS
void controlConfig(void) {
  pinMode(pinLB,OUTPUT); 
  pinMode(pinLF,OUTPUT); 
  pinMode(pinRB,OUTPUT); 
  pinMode(pinRF,OUTPUT);
  pinMode(L_PWM_PIN, OUTPUT);
  pinMode(R_PWM_PIN, OUTPUT);
}

// FUNÇÃO PARA CONTROLE DE VELOCIDADE DOS MOTORES
void setSpeed(unsigned char left, unsigned char right) {
  analogWrite(L_PWM_PIN, left); // O PINO DE VELOCIDADE DOS MOTORES ESQUERDO RECEBE UM VALOR DE VELOCIDADE
  analogWrite(R_PWM_PIN, right); // O PINO DE VELOCIDADE DOS MOTORES DIREITOS RECEBE UM VALOR DE VELOCIDADE
}

// FUNÇÃO PARA FAZER O CARRINHO AVANÇAR
void advance() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
  carState = 1;
}
// FUNÇÃO PARA FAZER O CARRINHO VIRAR À DIREITA
void turnRight() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
  carState = 4;
}
// FUNÇÃO PARA FAZER O CARRINHO VIRAR À ESQUERDA
void turnLeft() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
  carState = 3;
}
// FUNÇÃO PARA FAZER O CARRINHO VOLTAR
void back() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
  carState = 2;  
}
// FUNÇÃO PARA FAZER O CARRINHO PARAR
void stop() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, HIGH);
  carState = 5;
}

// FUNÇÃO PARA CONTROLE DO CARRINHO
void IRControl(void) {
  unsigned long key; 

  if (irrecv.decode(&results)) { // DECODIFICA O SINAL ENVIADO
    key = results.value; // ARMAZENA O VALOR NA VARIÁVEL "KEY"

    // SWITCH PARA CHAMAR AS FUNÇÕES DE ACORDO COM O BOTÃO PRESSIONADO
    switch(key) {
      case IR_GO: advance(); break;
      case IR_BACK: back(); break;
      case IR_LEFT: turnLeft(); break;
      case IR_RIGHT: turnRight(); break;
      case IR_STOP: stop(); break;
      default: break;
    }
    irrecv.resume(); // RECEBE O PRÓXIMO VALOR
  }
}

void setup() {
  controlConfig(); // CONFIGURAÇÕES DOS PINOS
  setSpeed(L_PWM_VAL, R_PWM_VAL); // DEFINE OS VALORES DE VELOCIDADE
  irrecv.enableIRIn(); // INICIA O RECEPTOR
  Serial.begin(9600); // INICIA O MONITOR SERIAL
  stop(); // O CARRINHO INICIALMENTE FICA PARADO
}

void loop() {
  IRControl(); // CHAMA A FUNÇÃO PARA CONTROLE DO CARRINHO
}
