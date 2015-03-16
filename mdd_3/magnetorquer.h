//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 16Mar15
//ADC for controlling a single-axis magnetorquer using an L298N H-Bridge

/*
 Arduino Pinout
 5V   - L298N Vss
 GND  - L298N GND
 Pin2 - L298N ENABLE
 Pin3 - L298N IN1
 Pin4 - L298N IN2
 Pin10 - LED1 + resistor to gnd (indicator for Pin2)
 Pin11 - LED2 + resistor to gnd (indicator for Pin3)
 Pin12 - LED3 + resistor to gnd (indicator for Pin4)
 */

//Pins
#define MT_ENABLE 2
#define MT_IN1 3
#define MT_IN2 4
#define MT_ENABLE_LED 10
#define MT_IN1_LED 11
#define MT_IN2_LED 12

#define MT_FWD 1
#define MT_REV (-1)
#define MT_MAX 255



//Initialises magnetorquer
//- returns 0 on success
int MT_init(void);

//Sets current direction and value for magnetorquer
//- dir is either FWD or REV, magnitude is between 0 and MAX inclusive
//- returns 0 on success, 1 if invalid dir, 2 if invalid magnitude
int MT_set(int dir, int magnitude);

void MT_stop();

