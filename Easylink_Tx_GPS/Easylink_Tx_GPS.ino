/*
  EasyLinkTx
  
  A basic EasyLink Transmit example..
  Read the analog value from A0 (pin 2) and copy the value into the tx packet.
  This Sketch is the counterpart of teh EasyLinkRx example.
  
  Hardware Required:
  * CC1310 LaunchPad
  
  This example code is in the public domain.
*/
#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTCC26XX.h>
#include "EasyLink.h"
const int sentenceSize = 80;
char sentence[sentenceSize];
char value[5];
int gps; // = "hello world";
//int test = 9;
int i=0; 
int currentTime = 0;
bool redOn = false;
bool greenOn = false;
int timeRedOn = 0;
int timeGreenOn = 0;

EasyLink_TxPacket txPacket;

EasyLink myLink;

void setup() {
  Serial.begin(115200);
  pinMode(GREEN_LED,OUTPUT); 
  pinMode(RED_LED,OUTPUT); 

  // begin defaults to EasyLink_Phy_50kbps2gfsk
  myLink.begin();
  //Serial.println(myLink.version());

  // Set the destination address to 0xaa
  txPacket.dstAddr[0] = 0xaa;
}

void loop() {
  currentTime = millis();
  if ((greenOn == true) && ((currentTime - timeGreenOn)>100)){
    digitalWrite(GREEN_LED, LOW);
    greenOn = false;
  }

  if ((redOn == true) && ((currentTime - timeRedOn)>100)){
    digitalWrite(RED_LED, LOW);
    redOn = false;
  }
  
  if (Serial.available()){
    //gps = Serial.readString();
    gps = Serial.read();
    digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    greenOn = true;
    timeGreenOn = millis(); 
    }
  //}
  else {
    digitalWrite(RED_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    redOn = true;
    timeRedOn = millis();
  }
  
  //uint16_t value = analogRead(A0);

  // Copy the analog value into the txPacket payload
  memcpy(&txPacket.payload, &gps, sizeof(int));

  // Set the length of the packet
  txPacket.len = sizeof(int);
  //Transmit immediately
  txPacket.absTime = EasyLink_ms_To_RadioTime(0);

  EasyLink_Status status = myLink.transmit(&txPacket);

  if(status == EasyLink_Status_Success) {
    //Serial.println("Packet transmitted successfully");
  } else {
    //Serial.print("Transmit failed with status code: ");
    //Serial.print(status);
    //Serial.print(" (");
    //Serial.print(myLink.getStatusString(status));
    //Serial.println(")");
  }

  delay(1000);
}
