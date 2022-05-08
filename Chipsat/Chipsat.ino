#include <LSM9DS1.h>
#include <LSM9DS1_Registers.h>
#include <LSM9DS1_Types.h>

/* 
This sketch will test all of the currently implemented sensor functionalities on the ChipSat
Will continuously check for commands that you can input. 
Set the Serial Monitor to 115200, type a number, and press the 'enter' key.
The command list is as follows:
1 - Read the IMU & Temperature Sensor
3 - Actuate Magnetorquers
4 - GPS (WIP)
*/
float CurrentTime = 0.0; //time in milliseconds
float LastSensorRead = 0.0; //time since last sensor read in milliseconds
float SensorReadInterval = 1*1000; //5*60*1000; // 5 second interval between sensor reads

// Important Pins //
int ADC0 = A0; //Light Sensor 1
int ADC1 = A1; // Light Sensor 2
int in1 = 25; // A4 -  For the Torque Coil Driver 
int in2 = 26; // A5 - For the Torque Coil Driver

// Other Variables //
char rx_byte;
String rx_str = "";
int rx_cmd = 0;
const int durationOn = 5000;
const int durationOff = 5000;
int timeTurnedOn = 0;
int timeTurnedOff = 0;
int currentTime;
int avgmag = 0;
bool isOn = false;
int scaling = 4096; // For Light Sensor

void set_light() {
  pinMode(ADC0, OUTPUT);
  pinMode(ADC1, OUTPUT);
  analogReadResolution(12);
}
// Torque coil driver settings
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

void ADCReadVolts(int pin) {
  int sensorval = analogRead(pin);
  int scaling = 4096;
  Serial.print("Light Sensor on pin ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.print( (float) ( (3.3 / scaling ) * sensorval )); 
  Serial.println( " Volts" );
  
  
}

void ADCRead(int pin) {
  int sensorval = analogRead(pin);
  Serial.print("Light Sensor on pin ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.println(sensorval); 
}



void set_IMU() {
// IMU
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


//
// Reads accelerometer, magnetometer, and gyroscope
//
void ReadIMU() {
    if (accelAvailable()) {
      readAccel();
      calcaRes();
      Serial.print("ax: ");
      Serial.print(calcAccel(ax)*9.81);//Accel[0]*9.81/1000);
      Serial.println(" m/s2");


      Serial.print("ay: ");
      Serial.print(calcAccel(ay)*9.81);
      Serial.println(" m/s2");

      Serial.print("az: ");
      Serial.print(calcAccel(az)*9.81);
      Serial.println(" m/s2");
      Serial.println("");             
    }

    if (magAvailable(ALL_AXIS)) {
      readMag();

      Serial.print("mx: ");
      Serial.print(calcMag(mx));
      Serial.println(" gauss"); 

    
      Serial.print("my: ");
      Serial.print(calcMag(my));
      Serial.println(" gauss"); 


      Serial.print("mz: ");
      Serial.print(calcMag(mz));
      Serial.println(" gauss"); 
      Serial.println("");             

    }
   
    if (gyroAvailable()) {
      readGyro();

      Serial.print("gx: ");
      Serial.print(calcGyro(gx));
      Serial.println(" dps"); 

    
      Serial.print("gy: ");
      Serial.print(calcGyro(gy));
      Serial.println(" dps"); 


      Serial.print("gz: ");
      Serial.print(calcGyro(gz));
      Serial.println(" dps"); 
      Serial.println("");             

    }    
    
}
//
// Performs command
// 1 to Read the IMU and temperature sensor, 2 to activate the torque coil driver
//
void performCommand() {
  if (rx_cmd == 1) {
    //Read IMU
    ReadIMU();
    
    
    // Read Temperature Sensor and convert
    Serial.print("Temperature is: ");
    readTemp();
    temperature = (float)(temperature/16 + 25);
    Serial.print(((float)temperature/16 +25 ));
    Serial.println(" Celsius");
    Serial.println("");
    //
    
  }


  else if ( rx_cmd == 2) {
    // Turns on the torque coild driver and reads the new magnetic field
    if (isOn == true && (currentTime - timeTurnedOn)>durationOn) {
         isOn = false;
         timeTurnedOff = millis();
         standby();
//       delay(1000);
// put outside if statement
      }

    else if (isOn == false && (currentTime - timeTurnedOff > durationOff)) {
      isOn = true;
      timeTurnedOn = millis();
      forward();
      }

      for (int i = 0; i < 100; i++) {
        if (magAvailable(ALL_AXIS)) {
          readMag();    
        }
        avgmag = avgmag + mz;
      }
      avgmag = avgmag /100;
//    Serial.print("standby - mz: ");
      Serial.println(100*calcMag(avgmag));
//    Serial.println(" gauss"); 
      avgmag = 0;
          
  }
  
}

void getCommand() {
    rx_byte = Serial.read();     // reads and stores the character

    // Tell teensy how to read commands
    if ((rx_byte >= '0') && (rx_byte <= '9')) {  // if the character is a positive number
      rx_str += rx_byte; // put the numbers together in a string
      // ex. "2" "2" becomes "22"
    }
    
    else if (rx_byte == '\n') {   // if end of command
      
      // Convert number string into an actual number
      rx_cmd = rx_str.toInt(); //ex. "22" becomes 22

      performCommand();
      
      rx_str = ""; // clears memory for next command
      rx_cmd = 0;     
    }
    
    else { // if enterted byte is not 0-9 or \n
      Serial.println("Invalid character in user input");
    } 
}
  
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  set_IMU();
  set_light();
}

// the loop routine runs over and over again forever:
void loop() {
  // Tell Launchpad to read computer commands
  CurrentTime = millis();
  if ((CurrentTime - LastSensorRead)>SensorReadInterval){ // if 5 minutes since last sensor read
    ADCRead(ADC0);
    ADCRead(ADC1);
    ADCReadVolts(ADC0);
    ADCReadVolts(ADC1);   
    LastSensorRead = millis();    
  }
  else if (Serial.available() > 0) {   // checks if a command is typed in
    getCommand();
  }  
}
