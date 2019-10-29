#include <QMC5883L.h>
#include <Wire.h>

int northLED = 5;
int southLED = 6;
int eastLED = 7;
int westLED = 8;
//boolean currentButton = LOW;
//int modeSelect = 2;
volatile byte directionSet = 0; //variable to inticate direction selected


int p = 0;
int motorPinLeft = 9;
int motorPinRight = 10;
QMC5883L compass;

void setup()
{
  Serial.begin(9600);
	Wire.begin();
  //attachInterrupt(digitalPinToInterrupt(modeSelect), changeDirection, FALLING);
	compass.init();
	compass.setSamplingRate(50);
  //pinMode(modeSelect, INPUT);
  
  pinMode(motorPinLeft, OUTPUT);
  pinMode(motorPinRight, OUTPUT);
  
  pinMode(northLED, OUTPUT);
  pinMode(southLED, OUTPUT);
  pinMode(eastLED, OUTPUT);
  pinMode(westLED, OUTPUT);
  
	Serial.begin(9600);
	Serial.println("QMC5883L Compass Demo");
	Serial.println("Turn compass in all directions to calibrate....");

 
}


void loop()
{
 Serial.println("Direction set is  ");
 Serial.println(directionSet);
	int r;
  int16_t x,y,z,t;
  r = compass.readRaw(&x,&y,&z,&t);

 	int heading = compass.readHeading();
  p = heading; //Reassignment here just incase I needed to do mathmatical manipulations to value
  Serial.println("direction is");
  Serial.println(p);
  Serial.println("Mode select ");
  Serial.println(directionSet);
  if(directionSet == 0){
    digitalWrite(northLED, LOW);
    digitalWrite(eastLED, HIGH);
    digitalWrite(southLED, HIGH);
    digitalWrite(westLED, HIGH);
  }
 if(directionSet == 1){
    digitalWrite(northLED, HIGH);
    digitalWrite(eastLED, LOW);
    digitalWrite(southLED, HIGH);
    digitalWrite(westLED, HIGH);
  }
   if(directionSet == 2){
    digitalWrite(northLED, HIGH);
    digitalWrite(eastLED, HIGH);
    digitalWrite(southLED, LOW);
    digitalWrite(westLED, HIGH);
  }
   if(directionSet == 3){
    digitalWrite(northLED, HIGH);
    digitalWrite(eastLED, HIGH);
    digitalWrite(southLED, HIGH);
    digitalWrite(westLED, LOW);
  }
  //Logic dependend on direction selected  
  switch (directionSet) {
    
    //Mode selected for Northward travel///////////////////////////////////////////////////////////////////////////////////////
    case 0:
    
    if((p > 355)||(p < 5)){
    Serial.println("Heading North");

    digitalWrite(motorPinLeft, HIGH);
    digitalWrite(motorPinRight, HIGH);
    
    
    //LED feedback for debugging only
    
//    /*digitalWrite(northLED, LOW);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);*/
  }
  
  if((p > 10) && (p < 90)){
    Serial.println("Slightly right");

    analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 128);
   
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, LOW);
//    digitalWrite(westLED, HIGH);
    
  }  

  if((p > 95) &&(p < 179)){
    Serial.println("Extremely Right");

    analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 255);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  } 

  if((p > 180) && (p < 269)){
    Serial.println("Extremely Left");

    analogWrite(motorPinLeft, 255);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  } 

   if((p > 270) && (p < 352)){
    Serial.println("Slightly Left");
   
    analogWrite(motorPinLeft, 128);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, LOW);
    
  } 
  delay(200);
  break;

// Mode selected for Eastward Travel///////////////////////////////////////////////////////////////////////////////////////////
  case 1:
   if((p > 85) && (p < 95)){
    Serial.println("Heading East");
    
    digitalWrite(motorPinLeft, LOW);
    digitalWrite(motorPinRight, LOW);
    
    //LED feedback for debugging only
    
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
  }
  
  if((p > 96) && (p < 179)){
    Serial.println("Slightly Right");
    
    analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 128);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, LOW);
    
  }  

  if((p > 180) &&(p < 269)){
    Serial.println("Extremely Right");
    
   analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 255);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  } 

  if((p > 181) && (p < 270)){
    Serial.println("Extremely Left");
    
    analogWrite(motorPinLeft, 255);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  } 

   if((p > 270) && (p < 360)){
    Serial.println("Slightly Left");
    
    analogWrite(motorPinLeft, 128);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, LOW);
//    digitalWrite(westLED, HIGH);
    
  } 
  delay(200);
  break;

//Mode selected for southward direction/////////////////////////////////////////////////////////////////
  case 2:
 if((p > 175) && (p < 185)){
    Serial.println("Heading South");
    
   digitalWrite(motorPinLeft, LOW);
    digitalWrite(motorPinRight, LOW);
    
    //LED feedback for debugging only
    
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
  }
  
  if((p > 186) && (p < 269)){
    Serial.println("Slightly Right");
    
    analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 128);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, LOW);
    
  }  

  if((p > 271) &&(p < 360)){
    Serial.println("Extremely Right");
    
   analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 255);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  } 

  if((p > 1) && (p < 90)){
    Serial.println("Extremely Left");
    
    analogWrite(motorPinLeft, 255);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  } 

   if((p > 91) && (p < 174)){
    Serial.println("Slightly Left");
    
    analogWrite(motorPinLeft, 128);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, LOW);
//    digitalWrite(westLED, HIGH);
    
  } 
  delay(200);
  break;

//Mode selected for Westward travel////////////////////////////////////////////////////////////////////////////////
  case 3:
   if((p > 265)&&(p < 275)){
    Serial.println("Heading West");
    
    digitalWrite(motorPinLeft, LOW);
    digitalWrite(motorPinRight, LOW);
    
    //LED feedback for debugging only
    
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, LOW);
  }
  
  if((p > 276) && (p < 360)){
    Serial.println("Slightly Right");
    
   analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 128);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, LOW);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  }  

  if((p > 1) &&(p < 89)){
    Serial.println("Extremely Right");
    
    analogWrite(motorPinLeft, 0);
    analogWrite(motorPinRight, 255);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, LOW);
//    digitalWrite(westLED, HIGH);
    
  } 

  if((p > 90) && (p < 179)){
    Serial.println("Extremely Left");
    
    analogWrite(motorPinLeft, 128);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, HIGH);
//    digitalWrite(eastLED, LOW);
//    digitalWrite(westLED, HIGH);
    
  } 

   if((p > 180) && (p < 360)){
    Serial.println("Slightly Left");
    
    analogWrite(motorPinLeft, 128);
    analogWrite(motorPinRight, 0);
    
    //LED feedback for debugging only
//    digitalWrite(northLED, HIGH);
//    digitalWrite(southLED, LOW);
//    digitalWrite(eastLED, HIGH);
//    digitalWrite(westLED, HIGH);
    
  } 
  break;
	}
 delay(200);
}


void changeDirection() {
  
  Serial.println("selecting new mode");
  if(directionSet < 3)
        directionSet = directionSet +1;
        else
        directionSet = 0;
        
  
  //detachInterrupt(digitalPinToInterrupt(modeSelect));
  //attachInterrupt(digitalPinToInterrupt(modeSelect), changeDirection, CHANGE);
  
}
