//Mark Yeo; mark.yeo@student.unsw.edu.au
//Last Modified 18Apr15
//Functions for DS3231 clock module

#define DS3231_I2C_ADDRESS 0x68

//Stores time since poweron in second, minute, hour
void CL_getTime(byte *second,byte *minute,byte *hour);


byte decToBcd(byte val);
byte bcdToDec(byte val);
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
void readDS3231time(byte *second,byte *minute,byte *hour,byte *dayOfWeek,byte *dayOfMonth,byte *month,byte *year);
void displayTime();

