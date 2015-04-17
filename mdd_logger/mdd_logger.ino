//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 18Apr15
//Measures change of magnetic field along magnometer's y-axis,
// then produces a magnetic field in the magnetorquer (aligned to y-axis) to oppose this change (B-Dot algorithm)
//Also logs data onto SD card (via SD card shield) in format: "[counter] [hour]h[minute]m[second]s {[x],[y],[z]}"

/*
 Arduino Pinout (+ SD shield: bend out SD shield A2-A3 legs & connect to GND & 5V respectively)
 GND  - MT GND
 A0-A5 - RT clock shield (line up SCL to A5)(daisychain MN on top)
 Pin2 - LED1 + resistor to gnd (mimics Pin5) (opt.)
 Pin3 - MN READY
 Pin4 - nothing (used by SD)
 Pin5 - MT ENABLE (grey)
 Pin6 - MT IN1 (yellow + green)
 Pin7 - MT IN2 (yellow + red)
 Pin8 - LED2 + resistor to gnd (green, mimics Pin6)
 Pin9 - LED3 + resistor to gnd (red, mimics Pin7)
 Pins10-13 - nothing (used by SD)
 
 */
 
/*Notes:
 - 'counter' variable resets to -1 every time serial monitor is opened
 */



#include <Wire.h>
#include <Adafruit_Sensor.h>
//Magnetorquer (MT)
#include "magnetorquer.h"
//Magnometer (MN)
#include <Adafruit_HMC5883_U.h>
#include "magnometer.h"
//SD logger (SD)
#include <SPI.h>
#include <SD.h>
//Clock (CL)
#include "clock.h"
#define X_DIR 0
#define Y_DIR 1
#define Z_DIR 2

//User-defined constants
#define MN_DELAY  100 //time between magnetorquer turning off and magnometer poll (ms)
#define MT_ON_TIME 100 //length of MT pulse (ms)
#define LOG_FILE_NAME "datalog6.txt" //name of log file (creates file if missing, else appends to existing)
#define MT_AXIS Y_DIR




Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345); //12345 is a random unique ID
int MT_event[2][3] = {{0,0,0},{0,0,0}};
int counter = -1;
const int chipSelect = 4; //SD logger variable
void SD_write (int MT_event[3], int counter);


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
  
  //Initialise clock
  setDS3231time(0,0,0,1,1,1,1);  //(t = 0) //seconds, minutes, hours, day, date, month, year
  
  //-1th MN poll
  MN_getEvent(mag, MT_event[1]);
  SD_write(MT_event[1],-1);
  counter = 0;
}


void loop() {
  delay(MN_DELAY); //pause between turning off MT & polling MN
  
  //Poll magnometer
  MN_getEvent(mag, MT_event[counter%2]);

  //Pulse magnetorquer accordingly
  if (MT_event[counter%2][MT_AXIS]     //current poll
    > MT_event[(counter+1)%2][MT_AXIS]){ //previous poll //check > or <?
    //If strength in magnetic field (on the axis of the MT) is increasing, pulse the MT 'forward'
    MT_set(MT_MAX, MT_FWD);
    delay(MT_ON_TIME);
    MT_stop();
  } else {
    //If strength in magnetic field is decreasing, pulse the MT in 'reverse'
    MT_set(MT_MAX, MT_REV);
    delay(MT_ON_TIME);
    MT_stop();
  }

  //Log data to SD card (counter, timestamp, magnetic strength in x,y,z)
  SD_write(MT_event[counter%2],counter);
  counter++;
}




//Write data to SD card (counter, timestamp, magnetic strength in x,y,z)
void SD_write (int MT_event[3], int counter){
  //Generate string to write to file,
  // in format: [counter] [hour]h[minute]m[second]s {[x],[y],[z]}
  
  //Poll #
  String dataString = "";
  dataString += String(counter);
  dataString += " ";
  
  //Timestamp
  byte second, minute, hour;
  CL_getTime(&second, &minute, &hour);  //read time
  dataString += String(hour);
  dataString += "h";
  if (minute<10){
    dataString += "0";
  }
  dataString += String(minute);
  dataString += "m";
  if (second<10){
    dataString += "0";
  }
  dataString += String(second);
  dataString += "s ";

  //Magnetic strength in x,y,z dir's
  dataString += "{";
  for (int i = 0; i < 3; i++){
    dataString += String(MT_event[i]);
    if (i < 2) {
      dataString += " ";
    } else {
      dataString += "}";
    }
  }
  
  //Write string to file
  File dataFile = SD.open(LOG_FILE_NAME, FILE_WRITE);
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




