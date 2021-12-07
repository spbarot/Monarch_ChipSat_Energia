#include "LSM9DS1_Registers.h"
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"
#include <ti/drivers/I2C.h>
//#include <ti/sysbios/knl/Clock.h>

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

//  configInt(XG_INT1, INT_DRDY_G, INT_ACTIVE_HIGH, INT_PUSH_PULL);
//  configInt(XG_INT2, INT_DRDY_XL, INT_ACTIVE_HIGH, INT_PUSH_PULL);


}

void loop() {
  // put your main code here, to run repeatedly:
int tx_ax;
int tx_ay;
int tx_az;
    
    if (accelAvailable()) {
      readAccel();
      tx_ax = ax;
      tx_ay = ay;
      tx_az = az;
      Serial.print("ax: ");
      Serial.println(ax);
    
      Serial.print("ay: ");
      Serial.println( ay);

      Serial.print("az: ");
      Serial.println(az);
      Serial.println(""); 
      delay(1000);
      
    }

//    if (magAvailable(ALL_AXIS)) {
//      readMag();
//      Serial.print("mx: ");
//      Serial.println(mx);
//    
//      Serial.print("my: ");
//      Serial.println(my);
//
//      Serial.print("mz: ");
//      Serial.println(mz);
//      Serial.println(""); 
//      delay(1000);
//    }
//    if (gyroAvailable()) {
//      readGyro();
//      Serial.print("gx: ");
//      Serial.println(gx);
//    
//      Serial.print("gy: ");
//      Serial.println(gy);
//
//      Serial.print("gz: ");
//      Serial.println(gz);
//      Serial.println(""); 
//      delay(1000);
//    }

}   
