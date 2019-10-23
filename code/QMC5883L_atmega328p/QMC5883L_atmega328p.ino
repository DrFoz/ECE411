#include <QMC5883L.h>
#include <Wire.h>
int x = 0;
int motorPin = 9;
QMC5883L compass;

void setup()
{
	Wire.begin();

	compass.init();
	compass.setSamplingRate(50);
  pinMode(motorPin, OUTPUT);
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

    if(x < 100){
    Serial.println("I'm calm");
    digitalWrite(motorPin, HIGH);
  }
  if(x > 101){
    Serial.println("Wrong way dummy");
    digitalWrite(motorPin, LOW);
  }
  
	}
 delay(1000);
}
