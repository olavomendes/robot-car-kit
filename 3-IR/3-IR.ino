#include <IRremote.h>

int RECV_PIN = 12; // PINO DO RECEPTOR(RECEIVER) DO SINAL IR
 
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // INICIA O RECEPTOR(RECEIVER)
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); // EXIBE OS RESULTADO EM FORMATO HEXADECIMAL
    irrecv.resume(); // RECEBE O PRÓXIMO VALOR
  }
}
