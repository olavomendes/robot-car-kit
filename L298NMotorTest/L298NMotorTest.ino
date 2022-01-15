// Entradas do L298N
int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;
int ENA = 5;
int ENB = 6;


void setup() {
  for (int i=2; i<=8; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Velocidade das rodas direitas
  analogWrite(ENA, 200);
  // Velocidade das rodas esquerdas
  analogWrite(ENB, 200);

  // Vai pra frente
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);

  // Para
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delay(2000);

  // Para - código alternativo
  // analogWrite(ENA, 0);
  // analogWrite(ENB, 0);
  
  // Volta
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);

  // Para novamente
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delay(2000);
}
