//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 16Mar15
//Measures change of magnetic field along magnometer's x-axis,
// then produces a magnetic field in the magnetorquer to oppose this change (B-Dot algorithm)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "magnetorquer.h"
#include "magnometer.h"
//RF
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//RF
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
unsigned long time;
char text[32];



//Assign unique id to mag
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  MT_init();
  MN_init(mag);
  
  //RF
  Serial.begin(57600);
  radio.begin();
  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.setChannel(65);
  radio.startListening();
}

int i;

void loop() {
  
  int MT_time = 200; //ms
  
  if (MN_bdot(mag, text) == MN_PLUS){ //check PLUS -> FWD?
    MT_set(MT_MAX, MT_FWD);
    delay(MT_time);
    MT_stop();
  } else {
    MT_set(MT_MAX, MT_REV);
    delay(MT_time);
    MT_stop();
  }
  
  
  
  radio.stopListening();
  radio.write(text,sizeof(text));
  radio.startListening();
  
  
}
