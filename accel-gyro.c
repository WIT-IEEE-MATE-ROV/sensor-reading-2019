// via https://github.com/adafruit/Adafruit_Python_LSM303/blob/master/Adafruit_LSM303/LSM303.py
// also look into https://github.com/ControlEverythingCommunity/LSM303DLHC/blob/master/C/LSM303DLHC.c

#include <stdio.h>
#include <wiringPiI2C.h>
#include "lsm303.h"

lsm303_accel_data accel_data;
lsm303_mag_data mag_data;

void setup(accel_address=LSM303_ADDRESS_ACCEL, mag_address=LSM303_ADDRESS_MAG){
  // Setup I2C interface
  accel_fd = wiringPiI2CSetup(accel_address);
  mag_fd = wiringPiI2CSetup(mag_address);
  //Enable accelerometer
  wiringPiI2CWrite(LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x27);
  //Enable magnetometer
  wiringPiI2CWrite(LSM303_REGISTER_MAG_MR_REG_M, 0x00);
}

void read(){
  //for accel, lsb data then msb
  accel_data_x1 = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_X_L_A);
  accel_data_x2 = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_X_H_A);
  accel_data.x = accel_data_x2 * 256 + accel_data_x2;
  if accel_data.x > 32767{
    accel_data.x -= 65536;
  }
  accel_data_y1 = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Y_L_A);
  accel_data_y1 = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Y_H_A);
  accel_data.y = accel_data_y2 * 256 + accel_data_y1;
  if accel_data.y > 32767{
    accel_data.y -= 65536;
  }
  accel_data_z1 = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Z_L_A);
  accel_data_z2 = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Z_H_A);
  accel_data.z = accel_data_z2 * 256 + accel_data_z1;
  if accel_data.z > 32767{
    accel_data.z -= 65536;
  }
  printf("Acceleration in X-Axis: %d\n", accel_data.x);
  printf("Acceleration in Y-Axis: %d\n", accel_data.y);
  printf("Acceleration in Z-Axis: %d\n", accel_data.z);
  //for accel, msb data then lsb
  mag_data_x1 = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_X_H_M);
  mag_data_x2 = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_X_L_M);
  mag_data.x = mag_data_x1 * 256 + mag_data_x2;
  if mag_data.x > 32767{
    mag_data.x -= 65536;
  }
  mag_data_y1 = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Y_H_M);
  mag_data_y2 = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Y_L_M);
  mag_data.y = mag_data_y1 * 256 + mag_data_y2;
  if mag_data.y > 32767{
    mag_data.y -= 65536;
  }
  mag_data_z1 = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Z_H_M);
  mag_data_z2 = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Z_L_M);
  mag_data.z = mag_data_z1 * 256 + mag_data_z2;
  if mag_data.z > 32767{
    mag_data.z -= 65536;
  }
  printf("Magnetic field in X-Axis: %d\n", mag_data.x);
  printf("Magnetic field in Y-Axis: %d\n", mag_data.y);
  printf("Magnetic field in Z-Axis: %d\n", mag_data.z);
}

void set_mag_gain(gain=LSM303_MAGGAIN_1_3){
  wiringPiI2CWrite(LSM303_REGISTER_MAG_MR_REG_M, gain)
}
