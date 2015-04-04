//Jabez Wilson : jabez.wilson@student.unsw.edu.au
//last edited  :  16 Mar 15
//program to detect the sign of change in flux with Adafruit HMC5883L breakout triple axis megnetometer

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

//number of millieseconds between checking two events from the magnetometer
#define MN_DELAY 200

//constants for plus and minus which is returned by return_direction
#define MN_PLUS 1
#define MN_MINUS (-1)

//'measurement ready' pin
#define MN_READY 48//check?

//function to make sure that the magnometer is connected
//returns 1 if mag is initialized 0 otherwise
int MN_init(Adafruit_HMC5883_Unified mag);

//function to return direction of the magnetic field to be activated by setMT
//return PLUS or MINUS
int MN_bdot(Adafruit_HMC5883_Unified mag, char text[32]);
