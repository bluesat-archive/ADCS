//Jabez Wilson : jabez.wilson@student.unsw.edu.au
//last edited  :  16 Mar 15
//program to detect the sign of change in flux with Adafruit HMC5883L breakout triple axis megnetometer

#include <Arduino.h>
#include"magnometer.h"

//function to make sure that the magnometer is connected
int MN_init(Adafruit_HMC5883_Unified mag){
  int ret = 1;
  if(!mag.begin()){
     //some error message?
    ret = 0;
  }
  return ret;
  pinMode(MN_READY, INPUT);
}

//function to return direction of required magnetic field
int MN_bdot(Adafruit_HMC5883_Unified mag){
  int ret;
  sensors_event_t event1, event2;
  
  mag.getEvent(&event1);
  delay(MN_DELAY);
  while (digitalRead(MN_READY) != 1){}//ensures MN is ready to measure (i.e. for v. small MN_DELAY)
  mag.getEvent(&event2);
  
  //only the sign of the difference is required
  if((event2.magnetic.x - event1.magnetic.x)<0){
    ret = MN_PLUS;
  } else {
    ret = MN_MINUS;
  }
  return ret;
}
