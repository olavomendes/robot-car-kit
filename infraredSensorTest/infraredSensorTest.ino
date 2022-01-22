s p#include <IRremote.h>

int InfraredReceiverPin = 12;
 
IRrecv irrecv(InfraredReceiverPin);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); 
    irrecv.resume(); // Recebe o próximo valor
  }
}
