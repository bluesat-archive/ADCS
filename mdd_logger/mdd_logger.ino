//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 13Apr15
//Measures change of magnetic field along magnometer's x-axis,
// then produces a magnetic field in the magnetorquer to oppose this change (B-Dot algorithm)
//Also logs data onto SD card (via SD card shield)

/*Notes:
- Pins 4,10-13 are used by SD card shield
- 'counter' variable resets to -1 every time serial monitor is opened
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "magnetorquer.h"
#include "magnometer.h"
#include <SPI.h>
#include <SD.h>
#define X_DIR 0
#define Y_DIR 1
#define Z_DIR 2
#define MN_DELAY  100 //time between turning off MT & polling MN (ms)
#define MT_ONTIME 100 //length of MT pulse (ms)

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345); //12345 is some random unique ID
int MT_event[2][3] = {{0,0,0},{0,0,0}};
int counter = -1;
const int chipSelect = 4; //SD logger variable
void writeToSD (int MT_event[3], int counter);





void setup() {
  MT_init();    //Initialise magnetorquer
  MN_init(mag); //Initialise magnometer
  
  //Initialise SD logger
  pinMode(10, OUTPUT); //if mega 53, else 10
  //SD.begin(chipSelect) //If serial debugging (below) disabled, uncomment this line
  
  //Begin code for serial debugging
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  //End code for serial debugging
  
  //-1th MN poll
  MN_getEvent(mag, MT_event[1]);
  writeToSD(MT_event[1],-1);
  counter = 0;
}


void loop() {
  //Poll magnometer
  delay(MN_DELAY); //time between MT turning off & polling MN
  MN_getEvent(mag, MT_event[counter%2]);

  //Pulse magnetorquer accordingly
  if (MT_event[counter%2][Y_DIR]-MT_event[(counter+1)%2][Y_DIR] > 0){ //check > or <?
    MT_set(MT_MAX, MT_FWD);
    delay(MT_ONTIME);
    MT_stop();
  } else {
    MT_set(MT_MAX, MT_REV);
    delay(MT_ONTIME);
    MT_stop();
  }

  //Log data to SD card
  writeToSD(MT_event[counter%2],counter);
  counter++;
}




//Write data to SD card
void writeToSD (int MT_event[3], int counter){
  String dataString = "";
  dataString += String(counter);
  dataString += ": {";
  for (int i = 0; i < 3; i++){
    dataString += String(MT_event[i]);
    if (i < 2) {
      dataString += " ";
    } else {
      dataString += "}";
    }
  }
  File dataFile = SD.open("datalog4.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();

    //Begin code for serial debugging
    Serial.println(dataString);
  } else {
    Serial.println("error opening file");
    //End code for serial debugging

  }
}




