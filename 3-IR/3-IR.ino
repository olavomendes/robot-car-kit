#include <IRremote.h>

int RECV_PIN = 12;

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // INICIA O "RECEIVER"
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // RECEBE O PRÓXIMO VALOR
  }
}
