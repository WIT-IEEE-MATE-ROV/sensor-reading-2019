// via https://github.com/adafruit/Adafruit_Python_LSM303/blob/master/Adafruit_LSM303/LSM303.py
// also look into https://github.com/ControlEverythingCommunity/LSM303DLHC/blob/master/C/LSM303DLHC.c

#include <stdio.h>
#include <wiringPiI2C.h>
#include "lsm303.h"

void setup(){
  // Setup I2C interface
  accel_fd = wiringPiI2CSetup(LSM303_ADDRESS_ACCEL);
  mag_fd = wiringPiI2CSetup(LSM303_ADDRESS_MAG);
  //Enable accelerometer
  wiringPiI2CWrite(LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x27);
  //Enable magnetometer
  wiringPiI2CWrite(LSM303_REGISTER_MAG_MR_REG_M, 0x00);
}

// Uses hexadecimal
void read_accel(){
  struct lsm303_accel_data accel_data;
  //for accel, lsb data then msb
  accel_data_xlo = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_X_L_A);
  accel_data_xhi = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_X_H_A);
  accel_data.x = accel_data_xhi * 0x100 + accel_data_xlo; // or (accel_data_xhi << 8) | accel_data_xlo;
  if accel_data.x > 0x7FFF{ // if accel_data.x > 0111111111111111
    accel_data.x -= 0x10000; //   accel_data.x -= 10000000000000000
  }
  accel_data_ylo = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Y_L_A);
  accel_data_yhi = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Y_H_A);
  accel_data.y = accel_data_yhi * 0x100 + accel_data_ylo;
  if accel_data.y > 0x7FFF{
    accel_data.y -= 0x10000;
  }
  accel_data_zlo = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Z_L_A);
  accel_data_zhi = wiringPiI2CRead(LSM303_REGISTER_ACCEL_OUT_Z_H_A);
  accel_data.z = accel_data_zhi * 0x100 + accel_data_zlo;
  if accel_data.z > 0x7FFF{
    accel_data.z -= 0x10000;
  }
  printf("Acceleration in X-Axis: %d\n", accel_data.x);
  printf("Acceleration in Y-Axis: %d\n", accel_data.y);
  printf("Acceleration in Z-Axis: %d\n", accel_data.z);

}

// Uses hexadecimal
void read_mag(){
  struct lsm303_mag_data mag_data;
  //for mag, msb data then lsb
  mag_data_xhi = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_X_H_M);
  mag_data_xlo = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_X_L_M);
  mag_data.x = mag_data_xlo + mag_data_xhi * 0x100; // or accel_data_xlo | (accel_data_xhi << 8);
  if mag_data.x > 0x7FFF{ // if accel_data.x > 0111111111111111
    mag_data.x -= 0x10000; //   accel_data.x -= 10000000000000000
  }
  mag_data_yhi = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Y_H_M);
  mag_data_ylo = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Y_L_M);
  mag_data.y = mag_data_ylo + mag_data_yhi * 0x100;
  if mag_data.y > 0x7FFF{
    mag_data.y -= 0x10000;
  }
  mag_data_zhi = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Z_H_M);
  mag_data_zlo = wiringPiI2CRead(LSM303_REGISTER_MAG_OUT_Z_L_M);
  mag_data.z = mag_data_zlo + mag_data_zhi * 0x100;
  if mag_data.z > 0x7FFF{
    mag_data.z -= 0x10000;
  }
  printf("Magnetic field in X-Axis: %d\n", mag_data.x);
  printf("Magnetic field in Y-Axis: %d\n", mag_data.y);
  printf("Magnetic field in Z-Axis: %d\n", mag_data.z);
}

void set_mag_gain(gain){
  wiringPiI2CWrite(LSM303_REGISTER_MAG_MR_REG_M, gain)
}

int main(void){
  setup();
  set_mag_gain(LSM303_MAGGAIN_1_3); // changes depending on what setting we want
  while (true){
   read_accel();
   read_mag();
  }
}
