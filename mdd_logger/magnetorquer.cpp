//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 22Feb15
//ADC implementation for controlling a magnetorquer using an L298N H-Bridge
// (.c extension doesn't work for some reason)


#include <Arduino.h>
#include "magnetorquer.h"


int MT_init() {
    pinMode(MT_ENABLE, OUTPUT);
    pinMode(MT_IN1, OUTPUT);
    pinMode(MT_IN2, OUTPUT);
    pinMode(MT_ENABLE_LED, OUTPUT);
    pinMode(MT_IN1_LED, OUTPUT);
    pinMode(MT_IN2_LED, OUTPUT);
    
    digitalWrite(MT_ENABLE, LOW);  //H-Bridge only works when ENABLE is HIGH
    digitalWrite(MT_ENABLE_LED, LOW);
    digitalWrite(MT_IN1, LOW);
    digitalWrite(MT_IN1_LED, LOW);
    digitalWrite(MT_IN2, LOW);
    digitalWrite(MT_IN2_LED, LOW);
    return 0;
}


int MT_set(int magnitude, int dir) {
    int ret;
    if (magnitude >= 0 && magnitude <= MT_MAX){
        if (dir == MT_FWD){
            analogWrite(MT_IN1, magnitude);
            analogWrite(MT_IN1_LED, magnitude);
            digitalWrite(MT_IN2, LOW);
            digitalWrite(MT_IN2_LED, LOW );
            ret = 0;
        } else if (dir == MT_REV){
            analogWrite(MT_IN2, magnitude);
            analogWrite(MT_IN2_LED, magnitude);
            digitalWrite(MT_IN1, LOW);
            digitalWrite(MT_IN1_LED, LOW );
            ret = 0;
        } else {
            ret = 1;//invalid direction
        }
    } else {
        ret = 2;    //invalid magnitude
    }
    return ret;
}

void MT_stop(){
  MT_set(0, MT_FWD);
}

