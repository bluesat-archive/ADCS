//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 18Apr15
//ADC for controlling a single-axis magnetorquer using an L298N H-Bridge


//Pins
#define MT_ENABLE 5
#define MT_IN1 6
#define MT_IN2 7
#define MT_ENABLE_LED 2
#define MT_IN1_LED 8
#define MT_IN2_LED 9

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

