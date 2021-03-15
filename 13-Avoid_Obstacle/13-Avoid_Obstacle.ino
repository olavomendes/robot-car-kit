#include <Servo.h>
#define L_PWM_PIN 5 // PINO DA VELOCIDADE DO LADO ESQUERDO
#define R_PWM_PIN 6 // PINO DA VELOCIDADE DO LADO DIREITO

Servo myServo;
int inputPin = A0; // ECHO
int outputPin = A1; // TRIG
int pinLB = 2; // RODA TRASEIRA ESQUERDA
int pinLF = 4; // RODA FRONTAL ESQUERDA
int pinRB = 7; // RODA TRASEIRA DIREITA
int pinRF = 8; // RODA FRONTAL ESQUERDA

unsigned char L_PWM_VAL = 120; // VELOCIDADE
unsigned char R_PWM_VAL = 120; // VELOCIDADE

int myAngle; // ÂNGULO
int pulseWidth;  // PW
unsigned char angle90 = 90; // ÂNGULO DE 90°



void controlConfig(void) {
  pinMode(pinLB,OUTPUT); 
  pinMode(pinLF,OUTPUT); 
  pinMode(pinRB,OUTPUT); 
  pinMode(pinRF,OUTPUT); 
  pinMode(L_PWM_PIN, OUTPUT);
  pinMode(R_PWM_PIN, OUTPUT);
}

// FUNÇÃO PARA A VELOCIDADE DO CARRINHO
void setSpeed(unsigned char left, unsigned char right) {
  analogWrite(L_PWM_PIN, left); // PASSA A VELOCIDADE DEFINIDA ACIMA (L_PWM_VAL) PARA O PINO DA VELOCIDADE
  analogWrite(R_PWM_PIN, right);
}

// FUNÇÃO PARA ANDAR PARA FRENTE
void advance() {
  // NOTE QUE AS RODAS DE AMBOS OS LADOS (DIREITO E ESQUERDO) DEVEM SEGUIR O MESMO FLUXO
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
}

// FUNÇÃO PARA VIRAR À DIREITA 
void turnRight() {
  // NOTE QUE AS RODAS DE AMBOS OS LADOS (DIREITO E ESQUERDO) DEVEM SEGUIR UM FLUXO OPOSTO
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
}

// FUNÇÃO PARA VIRAR À ESQUERDA
void turnLeft() {
  // NOTE QUE AS RODAS DE AMBOS OS LADOS (DIREITO E ESQUERDO) DEVEM SEGUIR UM FLUXO OPOSTO
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
}

// FUNÇÃO PARA PARAR O CARRINHO
void stop() {
  // NOTE QUE AS RODAS DE AMBOS OS LADOS (DIREITO E ESQUERDO) DEVEM ESTAR COMO "HIGH"
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, HIGH);
}

// FUNÇÃO PARA VOLTAR
void back() {
  // NOTE QUE AS RODAS DE AMBOS OS LADOS (DIREITO E ESQUERDO) DEVEM SEGUIR O MESMO FLUXO, QUE É O FLUXO CONTRÁRIO AO DA FUNÇÃO "ADVANCE"
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
}

// FUNÇÃO PARA O CARRINHO CONTROLAR A PRÓPRIA DIREÇÃO
void selfControl(void) {
  int H;
  myServo.write(angle90); // O SERVO FICA EM 90°
  H = ultrasonicRaging(1); // A FUNÇÃO RECEBE O MODO 1, QUE É "AVANÇAR"
  delay(300);

  // SE A DISTÂNCIA FOR MENOR QUE 15 CM, O CARRINHO PARA E VOLTA 
  if (ultrasonicRaging(1) < 15) { 
    stop(); // PARA
    delay(100);
    back(); // VOLTA
    delay(50);
  }

  // SE A DISTÂNCIA FOR MENOR QUE 30 CM
  if (ultrasonicRaging(1) < 30) {
    stop(); // PARA
    delay(100);
    myServo.write(0); // SERVO FICA NO ÂNGULO 0°
    int L = askPinL(2); // MEDE A DISTÂNCIA À ESQUERDA
    delay(300);
    myServo.write(180); // SERVO FICA NO ÂNGULO 180°
    int R = askPinR(3); // MEDE A DISTÂNCIA À DIREITA
    delay(300);

    // SE A DISTÂNCIA DA ESQUERDA FOR MAIOR QUE DA DIREITA
    // O CARRINHO VIRA À ESQUERDA
    if (askPinL(2) > askPinR(3)) {
      back(); // RETORNA
      delay(100);
      turnLeft(); // VIRA À ESQUERDA
      delay(400);
      stop(); // PARA
      delay(50);
      myServo.write(angle90); // SERVO FICA NO ÂNGULO DE 90°
      H = ultrasonicRaging(1); // MEDE A DISTÂNCIA ATÉ O OBJETO QUE ESTÁ NA FRENTE
      delay(500);
    }

    // SE A DISTÂNCIA DA ESQUERDA FOR MENOR OU IGUAL À DA DIREITA
    // O CARRINHO VIRA À DIREITA
    if (askPinL(2) <= askPinR(3)) {
      back(); // RETORNA
      delay(100);
      turnRight(); // VIRA À DIREITA
      delay(400);
      stop(); // PARA
      delay(50);
      myServo.write(angle90); // SERVO FICA NO ÂNGULO DE 90°
      H = ultrasonicRaging(1); // MEDE A DISTÂNCIA ATÉ O OBJETO QUE ESTÁ NA FRENTE
      delay(300);      
    }
    
    // SE A DISTÂNCIA DA ESQUERDA E DÁ DIREITA FOREM MENORES QUE 35 CM
    // O CARRINHO PARA E VOLTA
    if (askPinL(2) < 35 && askPinR(3) < 35) {
      stop(); // PARA
      delay(50);
      back(); // VOLTA
      delay(50);
    }
    // CASO O CARRINHO TENHA ESPAÇO SUFICIENTE (SEM OBJETOS NA FRENTE), ELE AVANÇA
  } else {
    advance(); // AVANÇA
  }
}

// FUNÇÃO PARA MEDIR A DISTÂNCIA ATÉ UM OBJETO
int ultrasonicRaging(unsigned char mode) {
  int oldDistance;

  // SINAL ULTRASSÔNICO É ENVIADO (LIGADO E DESLIGADO) NO INTERVALO DE MICROSEGUNDOS
  digitalWrite(outputPin, LOW);
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);

  int distance = pulseIn(inputPin, HIGH); // LÊ A DURAÇÃO DO "HIGH"
  distance = distance / 58; // TRANSFORMA "PULSO" PARA "DISTÂNCIA"

  // SE O MODO FOR 1, EXIBE E RETORNA A DISTÂNCIA
  if (mode == 1) {
    Serial.print("\n H = ");
    Serial.print(distance, DEC);
    return distance;
  } else {
    return distance;
  }
}


int askPinL(unsigned char mode) {
  int oldLDistance;
  digitalWrite(outputPin, LOW);
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);

  int leftDistance = pulseIn(inputPin, HIGH); // LÊ A DURAÇÃO DO "HIGH"
  leftDistance = leftDistance / 58; // TRANSFORMA "PULSO" PARA "DISTÂNCIA"

  // SE O MODO FOR 2, EXIBE E RETORNA A DISTÂNCIA À ESQUERDA DO CARRINHO
  if (mode == 2) {
    Serial.print("\n L = ");
    Serial.print(leftDistance, DEC);
    return leftDistance;
  } else {
    return leftDistance;
  }
}

int askPinR(unsigned char mode) {
  int oldRDistance;
  digitalWrite(outputPin, LOW);
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);

  int rightDistance = pulseIn(inputPin, HIGH); // LÊ A DURAÇÃO DO "HIGH"
  rightDistance = rightDistance / 58; // TRANSFORMA "PULSO" PARA "DISTÂNCIA"

  // SE O MODO FOR 3, EXIBE E RETORNA A DISTÂNCIA À DIREITA DO CARRINHO
  if (mode == 3) {
    Serial.print("\n R = ");
    Serial.print(rightDistance, DEC);
    return rightDistance;
  } else {
    return rightDistance;
  }
}

void setup() {
  myServo.attach(A2);
  controlConfig();
  setSpeed(L_PWM_VAL, R_PWM_VAL);
  myServo.write(angle90);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
  stop();
  delay(1000);
}

void loop() {
  selfControl();
}