#include <Wire.h>
#define address 0x1E //0011110b, I2C 7bit address of HMC5883
int motorPin = 9;

void setup(){  
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  Wire.begin();  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop(){
  
  int x,y,z; //triple axis data
  int xmin,xmax,ymin,ymax,zmin,zmax;
  xmin=0; xmax=0; ymax=0; ymin = 0; zmin=0;zmax=0;
  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  if(-40 < x < 40){
    Serial.println("I'm calm");
    digitalWrite(motorPin, HIGH);
  }
  if(x > 41){
    Serial.println("Wrong way dummy");
    digitalWrite(motorPin, LOW);
  }
  if(x < -41){
    Serial.println("Getting warmer idiot");
    digitalWrite(motorPin, LOW);
  }
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z); 

   delay(1000);
}
