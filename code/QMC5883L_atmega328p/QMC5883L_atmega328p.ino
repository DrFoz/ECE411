#include <QMC5883L.h>
#include <Wire.h>

int northLED = 5;
int southLED = 6;
int eastLED = 7;
int westLED = 8;


int x = 0;
int motorPin = 9;
QMC5883L compass;

void setup()
{
	Wire.begin();

	compass.init();
	compass.setSamplingRate(50);
  pinMode(motorPin, OUTPUT);
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
	int heading = compass.readHeading();
	if(heading==0) {
		/* Still calibrating, so measure but don't print */
	} else {
		Serial.println(heading);
    x = heading;

    if(x < 50){
    Serial.println("I'm calm");
    digitalWrite(motorPin, HIGH);
    digitalWrite(northLED, LOW);
    digitalWrite(southLED, HIGH);
  }
  if(x > 101){
    Serial.println("Wrong way dummy");
    digitalWrite(motorPin, LOW);
    digitalWrite(southLED, LOW);
    digitalWrite(northLED, HIGH);
    
  }
  
	}
 delay(100);
}
