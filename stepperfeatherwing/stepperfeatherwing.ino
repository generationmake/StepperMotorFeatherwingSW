#include "tmc5130.h"

TMC5130 tmc1(5); // stepper 1
TMC5130 tmc2(4); // stepper 2
#define EMERGENCYSTOP A4

//returns false if emergency button is not activated
bool emergencybutton(void)
{
  return digitalRead(EMERGENCYSTOP);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(EMERGENCYSTOP,  INPUT_PULLDOWN);   // set EMERGENCYSTOP pin to input with pull down
  delay(4000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("setup SPI for TMC");
  setupSpiForTMC();
  Serial.println("done");
  Serial.println("setup TMC");
  tmc1.begin();
  tmc2.begin();
  Serial.println("done");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void loop() {
  if(emergencybutton())
  {
    Serial.println("emergency button active");    
  }
  else
  {
    tmc1.move(51200, false); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.move(51200, false); // should be one turn with 1.8 degrees and 256 micro steps
    digitalWrite(LED_BUILTIN, HIGH);
    delay(4000);
    tmc1.move(0, false); // should be one turn back with 1.8 degrees and 256 micro steps
    tmc2.move(0, false); // should be one turn back with 1.8 degrees and 256 micro steps
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(4000);

}
