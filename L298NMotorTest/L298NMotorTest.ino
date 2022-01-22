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
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(2000);
}
