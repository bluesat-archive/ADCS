#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_PWMServoDriver.h>

#define MAXDIFF 50 //change this

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
int prev, curr, diff, pwmval;
sensors_event_t event; 


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(1600);
  mag.enableAutoRange(true);
  mag.begin();
}


void loop() {
  mag.getEvent(&event);
  prev = event.magnetic.x;
  mag.getEvent(&event);
  curr = event.magnetic.x;
  Serial.print(prev);
  Serial.println(curr);
  diff = curr - prev;

  pwmval = diff * 4096 / MAXDIFF;

  if (pwmval > 0){
    pwm.setPWM(0, 0, pwmval); //pin 0, 0-4096
    pwm.setPWM(1, 0, 0);      //pin 1, GND
  } else {
    pwm.setPWM(0, 0, 0);      //pin 0, 0-4096
    pwm.setPWM(1, 0, pwmval); //pin 1, GND
  }
  delay(500);
  pwm.setPWM(0, 0, 0); //pin 0, 0-4096
  pwm.setPWM(1, 0, 0);
}
