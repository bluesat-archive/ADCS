//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 16Mar15
//Measures change of magnetic field along magnometer's x-axis,
// then produces a magnetic field in the magnetorquer to oppose this change (B-Dot algorithm)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "magnetorquer.h"
#include "magnometer.h"



//Assign unique id to mag
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  MT_init();
  MN_init(mag);
}

void loop() {
  int MT_time = 500; //ms
  
  if (MN_bdot(mag) == MN_PLUS){ //check PLUS -> FWD?
    MT_set(MT_MAX, MT_FWD);
    delay(MT_time);
    MT_stop();
  }
  
  if (MN_bdot(mag) == MN_MINUS){
    MT_set(MT_MAX, MT_REV);
    delay(MT_time);
    MT_stop;
  }
}
