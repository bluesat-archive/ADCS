//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 16Mar15
//Measures change of magnetic field along magnometer's x-axis,
// then produces a magnetic field in the magnetorquer to oppose this change (B-Dot algorithm)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "magnetorquer.h"
#include "magnometer.h"
//logger
#include <SPI.h>
#include <SD.h>
#define Y_DIR 1
const int chipSelect = 4;



//Assign unique id to mag
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  
  MT_init();
  MN_init(mag);
  
  //logger
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT); //hardware chip select pin - 53 on mega, else 10
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

int event1[3];
int event2[3];
int counter = 0;
int MT_Ontime = 200; //ms

void loop() {
  
  //Poll magnometer twice
  MN_getEvent(mag, event1);
  delay (MN_DELAY);
  MN_getEvent(mag, event2);

  //Idea - poll/torque/poll/torque/etc. (instead of poll/poll/torque/etc.)
  

  //Pulse magnetorquer accordingly
  if (event1[Y_DIR]-event2[Y_DIR] > 0){ //check PLUS -> FWD?
    MT_set(MT_MAX, MT_FWD);
    delay(MT_Ontime);
    MT_stop();
  } else {
    MT_set(MT_MAX, MT_REV);
    delay(MT_Ontime);
    MT_stop();
  }


  writeToSD(event1,event2,counter);
  counter++;
}





void writeToSD (int event1[3], int event2[3], int counter){
  //Write data to log:
  String dataString = "";
  dataString += String(counter);
  dataString += ": {";
  for (int i = 0; i < 3; i++){
    dataString += String(event1[i]);
    if (i < 2) {
      dataString += " ";
    } else {
      dataString += "},{";
    }
  }
  for (int i = 0; i < 3; i++){
    dataString += String(event2[i]);
    if (i < 2) {
      dataString += " ";
    } else {
      dataString += "}";
    }
  }
  File dataFile = SD.open("datalog2.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  } else {
    Serial.println("error opening file");
  }
}




