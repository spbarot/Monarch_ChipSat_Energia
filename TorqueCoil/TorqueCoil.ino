#include <LSM9DS1.h>
#include <LSM9DS1_Registers.h>
#include <LSM9DS1_Types.h>

int in1 = 25; // A4 PWM1
int in2 = 26; // A5 PWM2
bool isOn = false;
const int durationOn = 5000;
const int durationOff = 5000;
int timeTurnedOn = 0;
int timeTurnedOff = 0;
int currentTime;
int avgmag = 0;


void forward(void) {
  //put your main code here, to run repeatedly:
  digitalWrite(in1, HIGH);    //To move forward
  digitalWrite(in2, LOW);
//  digitalWrite(enA, HIGH); //Slow speed


}

void standby(void) {
  //put your main code here, to run repeatedly:
  digitalWrite(in1, LOW);    //To move forward
  digitalWrite(in2, LOW);
//  digitalWrite(enA, 100); //Slow speed

}

void reverse(void) {
  //put your main code here, to run repeatedly:
  digitalWrite(in1, LOW);    //To move forward
  digitalWrite(in2, HIGH);
//  digitalWrite(enA, 255); //Slow speed

}

void brake(void) {
  //put your main code here, to run repeatedly:
  digitalWrite(in1, HIGH);    //To move forward
  digitalWrite(in2, HIGH);
//  digitalWrite(enA, 100); //Slow speed
}


void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(115200);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  I2C_init();
  initI2C();
  LSM9DS1init();
  LSM9DS1begin();
  readAccel();
  readMag();
  readGyro();
  configInt(XG_INT1, INT_DRDY_G, INT_ACTIVE_HIGH, INT_PUSH_PULL);
  configInt(XG_INT2, INT_DRDY_XL, INT_ACTIVE_HIGH, INT_PUSH_PULL);

  
}


void loop(){
  // put your main code here, to run repeatedly: 
  currentTime = millis();
  
  if (isOn == true && (currentTime - timeTurnedOn)>durationOn) {
         isOn = false;
         timeTurnedOff = millis();
         standby();
//         delay(1000);
// put outside if statement

  }

  else if (isOn == false && (currentTime - timeTurnedOff > durationOff)) {
       isOn = true;
       timeTurnedOn = millis();
       forward();
//       delay(1000);
//       for ( int i = 0; i < 100; i++) {
//         if (magAvailable(ALL_AXIS)) {
//           readMag();
//         }
//         avgmag = avgmag + mz;
//       }
//         avgmag = avgmag/100;
//         Serial.print("forward - mz: ");
//         Serial.print(100*calcMag(avgmag));
//         Serial.println(" gauss"); 
       }


        for (int i = 0; i < 100; i++) {
          if (magAvailable(ALL_AXIS)) {
            readMag();    
          }
          avgmag = avgmag + mz;
        }
        avgmag = avgmag /100;
//      Serial.print("standby - mz: ");
        Serial.println(100*calcMag(avgmag));
//      Serial.println(" gauss"); 
        avgmag = 0;

       
  }
  
