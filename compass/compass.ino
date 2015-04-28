//Simple N/S compass
//HMC5883L in A4 (SDA), A5 (SCL)
//LED-Resistors in 2 (south), 8 (north)



#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#define NORTHCOPY 13
#define NORTH 9
#define SOUTH 2

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup(void){
  pinMode(NORTHCOPY, OUTPUT);
  pinMode(NORTH, OUTPUT);
  pinMode(SOUTH, OUTPUT);
  Serial.begin(9600);
  mag.begin();
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
  
  if (event.magnetic.y > 0){
    digitalWrite(NORTHCOPY, HIGH);
    digitalWrite(NORTH, HIGH);
    digitalWrite(SOUTH, LOW);
  } else {
    digitalWrite(NORTHCOPY, LOW);
    digitalWrite(NORTH, LOW);
    digitalWrite(SOUTH, HIGH);
  }
  Serial.println(event.magnetic.y);

  delay(10);
}


