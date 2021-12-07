//#include <ti/drivers/PIN.h>
//#include <ti/drivers/pin/PINCC26XX.h>
//#include "C:\Users\efahk\AppData\Local\Energia15\packages\energia\hardware\cc13xx\4.9.1\variants\LAUNCHXL_CC1310\pins.c"

int sensorval = 0;
int scaling = 4096;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  analogReadResolution(12);
}

float ADCReadVolts(int pin) {
  sensorval = analogRead(pin);
  int scaling = 4096;
  return (float) ( (3.3 / scaling ) * sensorval ); 
}
//
//float ADCReadVolts(int pin) {
//  sensorval = analogRead(pin);
//  int scaling = 4096;
//  return (float) ( (3.3 / scaling ) * sensorval ); 
//}

void loop() {
  // put your main code here, to run repeatedly: 
  //digitalWrite(A0,HIGH);
  //delay(100);
  float valV = ADCReadVolts(A0);
  Serial.println(valV);
  if (valV >= 1.0 ) {
    digitalWrite(40,LOW);
    digitalWrite(39,HIGH);
  }
  else {
    digitalWrite(39,LOW);
    digitalWrite(40,HIGH);    
  }

  
}
