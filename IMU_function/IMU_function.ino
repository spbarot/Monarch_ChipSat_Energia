#include "LSM9DS1_Registers.h"
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"
#include <ti/drivers/I2C.h>

void setup() {
  // put your setup code here, to run once:
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

void loop() {
  // put your main code here, to run repeatedly:

//    if (accelAvailable()) {
//      readAccel();
//      calcaRes();
//      //convertAccel(ax,ay,az,Accel); // convert raw Accel values to m/s2 
//      Serial.print("ax: ");
//      Serial.print(calcAccel(ax)*9.81);//Accel[0]*9.81/1000);
//      Serial.println(" m/s2");
//
//
//      Serial.print("ay: ");
//      Serial.print(calcAccel(ay)*9.81);
//      Serial.println(" m/s2");
//
//      Serial.print("az: ");
//      Serial.print(calcAccel(az)*9.81);
//      Serial.println(" m/s2");
//      Serial.println("");       
//      delay(1000);
//      
//    }

//    Serial.print("");
//
//
//    if (magAvailable(ALL_AXIS)) {
//      readMag();
//
//      Serial.print("mx: ");
//      Serial.print(calcMag(mx));
//      Serial.println(" gauss"); 
//
//    
//      Serial.print("my: ");
//      Serial.print(calcMag(my));
//      Serial.println(" gauss"); 
//
//
//      Serial.print("mz: ");
//      Serial.print(calcMag(mz));
//      Serial.println(" gauss"); 
//      delay(1000);
//    }

    Serial.println("");
    Serial.print("Temperature is: ");
    readTemp();
    temperature = (float)(temperature/16 + 25);
    Serial.print(temperature/16 + 25);
//    Serial.print(((float)temperature/16 +25 ));

    
//    if (gyroAvailable()) {
//      readGyro();
//
//      Serial.print("gx: ");
//      Serial.print(calcGyro(gx));
//      Serial.println(" dps"); 
//
//    
//      Serial.print("gy: ");
//      Serial.print(calcGyro(gy));
//      Serial.println(" dps"); 
//
//
//      Serial.print("gz: ");
//      Serial.print(calcGyro(gz));
//      Serial.println(" dps"); 
//      delay(1000);
//    }
//
//    Serial.println("");
    


}   
