// via https://github.com/adafruit/Adafruit_Python_LSM303/blob/master/Adafruit_LSM303/LSM303.py
// also look into https://github.com/ControlEverythingCommunity/LSM303DLHC/blob/master/C/LSM303DLHC.c

#include <stdio.h>
#include <wiringPiI2C.h>
#include <lsm303.h>

void setup(accel_address=LSM303_ADDRESS_ACCEL, mag_address=LSM303_ADDRESS_MAG){
  // Setup I2C interface
  accel_fd = wiringPiI2CSetup(accel_address);
  mag_fd = wiringPiI2CSetup(mag_address);
  //Enable accelerometer
  wiringPiI2CWrite(LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x27)
}

void read(){
  accel_raw = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_X_L_A);
  mag_raw = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_X_H_M);
}

void set_mag_gain(gain=LSM303_MAGGAIN_1_3){
  wiringPiI2CWrite(LSM303_REGISTER_MAG_MR_REG_M, gain)
}
