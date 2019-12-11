/* Start of Code */

#include <Wire.h>
#include <HMC5883L.h>

//heptic motor
int motorPin = 9;

//leds to indicate direction
int LED_n = 5;
int LED_e = 7;
int LED_s = 6;
int LED_w = 8;

int req_direction = 0;
  
int speed = 255;
int prev_speed = 255;

//change direction button
int buttonPin = 2;

int curr_direction = 1;
int buttonState = 0;  
int lastButtonState = 0;  

HMC5883L compass;

void setup(){
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(LED_n, OUTPUT);
  pinMode(LED_e, OUTPUT);
  pinMode(LED_s, OUTPUT);
  pinMode(LED_w, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  analogWrite(motorPin, 255);
  Wire.begin();
  
  digitalWrite(LED_n, LOW);
  digitalWrite(LED_e, HIGH);
  digitalWrite(LED_s, HIGH);
  digitalWrite(LED_w, HIGH);
  
  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);
  
  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  
  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  
  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);
  
  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(82, -290);
}

void loop() {
  handle_button();
}

void handle_button() {
  //int req_direction = 0;
  
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      
      //1 = N | 2 = E | 3 = S | 4 = W
      curr_direction++;
      
      Serial.print("current direction : ");
      Serial.println(curr_direction);
    }
    
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  float heading = get_direction();
  
  if (curr_direction == 1) {
    digitalWrite(LED_n, LOW);
    digitalWrite(LED_e, HIGH);
    digitalWrite(LED_s, HIGH);
    digitalWrite(LED_w, HIGH);
    req_direction = 0;
  } else if (curr_direction == 2) {
    digitalWrite(LED_n, HIGH);
    digitalWrite(LED_e, LOW);
    digitalWrite(LED_s, HIGH);
    digitalWrite(LED_w, HIGH);
    req_direction = 90;
  } else if (curr_direction == 3) {
    digitalWrite(LED_n, HIGH);
    digitalWrite(LED_e, HIGH);
    digitalWrite(LED_s, LOW);
    digitalWrite(LED_w, HIGH);
    req_direction = 180;
  } else if (curr_direction == 4) {
    digitalWrite(LED_n, HIGH);
    digitalWrite(LED_e, HIGH);
    digitalWrite(LED_s, HIGH);
    digitalWrite(LED_w, LOW);
    curr_direction  = 0;
    req_direction   = 270;
  }
  //need to handle if N and req_direction minus 5 is -5 and it needs to be 355
  if (heading > (req_direction - 5) && heading < (req_direction + 5)) {
    speed = 255;
    Serial.println("(90 - 5) Heading ");  
    Serial.println(heading);  
    Serial.println("(90 - 5) req_direction ");  
    Serial.println(req_direction);  
  } else if (heading < (req_direction - 5) && heading > (req_direction - (req_direction / 2))) {
    speed = 0;
    Serial.println("low Heading ");  
    Serial.println(heading);  
    Serial.println("low req_direction ");  
    Serial.println(req_direction);  
  }
  
  Serial.println("Heading ");  
  Serial.println(heading);  
  Serial.println("prev_speed ");  
  Serial.println(prev_speed);  
  Serial.println("speed ");  
  Serial.println(speed);  

  if (prev_speed != speed){
    if (speed >= 0 && speed <= 255) {
      analogWrite(motorPin, speed);
      delay(1000);
    }
  }
  prev_speed = speed;
}

float get_direction() {
  Vector norm = compass.readNormalize();
  
  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);
  
  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Montreal,QC declination angle is -14'35W (negative)
  // portland +15 2'
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (15.0 + (2.0 / 60.0)) / (180 / M_PI);
  //float declinationAngle = (-15.0-(2.0/60.0)) / (180 / M_PI);;
  //heading -= declinationAngle;
  //heading += 0.26;
  
  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
    heading += 2 * PI;
  
  
  if (heading > 2 * PI)
    heading -= 2 * PI;
  
  // Convert to degrees
  float headingDegrees = heading * (180/M_PI); 
  
  //Serial.println("BEFotr ");
  //Serial.println(headingDegrees);
  
  delay(100);
  return headingDegrees;
}

/* End of Code */
