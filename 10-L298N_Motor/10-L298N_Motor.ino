// ENTRADAS DO L298N
int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;
int ENA = 5;
int ENB = 6;


void setup() {
  for (int i=2; i<9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // VELOCIDADE DAS RODAS DA DIREITA
  analogWrite(ENA, 200);
  // VELOCIDADE DAS RODAS DA ESQUERDA
  analogWrite(ENB, 200);

  // RODAS DA DIREITA / DIREÇÃO: FRENTE
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // RODAS DA ESQUERDA / DIREÇÃO: FRENTE
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);

  // TODOS AS RODAS PARAM PARAM
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delay(2000);

  // TODAS AS RODAS PARAM (ALGORITMO OPCIONAL)
  // analogWrite(ENA, 0);
  // analogWrite(ENB, 0);
  
  // DIREÇÃO: TRÁS
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);

  // TODOS OS MOTORES PARAM
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delay(2000);

}
