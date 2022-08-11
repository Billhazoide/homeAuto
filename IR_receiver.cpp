#include<IRremote.h>
IRrecv  irrecv(12);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("Start");
}

void loop() {
  if(irrecv.decode(&results))  {
    Serial.print(results.value, DEC);
    Serial.print("    ");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }

}