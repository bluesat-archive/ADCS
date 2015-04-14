//Jabez Wilson : jabez.wilson@student.unsw.edu.au
//Mark Yeo: mark.yeo@student.unsw.edu.au
//Last Modified  :  13Apr15
//Magnometer (Adafruit HMC5883L) functions for the Magnetic Detumbler Demo

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


void MN_getEvent(Adafruit_HMC5883_Unified mag, int eventOut[3]){
  sensors_event_t eventIn;
  mag.getEvent(&eventIn);
  //while (digitalRead(MN_READY) != 1){}//ensures MN is ready to measure (i.e. for v. small MN_DELAY) //not firing w/ uno
  eventOut[0] = eventIn.magnetic.x;
  eventOut[1] = eventIn.magnetic.y;
  eventOut[2] = eventIn.magnetic.z;
}
