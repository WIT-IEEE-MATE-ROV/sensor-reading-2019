// via https://github.com/adafruit/Adafruit_Python_LSM303/blob/master/Adafruit_LSM303/LSM303.py
// also look into https://github.com/ControlEverythingCommunity/LSM303DLHC/blob/master/C/LSM303DLHC.c

#include <wiringPiI2C.h>

LSM303_ADDRESS_ACCEL = (0x32 >> 1);  # 0011001x
LSM303_ADDRESS_MAG   = (0x3C >> 1);  # 0011110x
                                         // Default    Type
LSM303_REGISTER_ACCEL_CTRL_REG1_A = 0x20; // 00000111   rw
LSM303_REGISTER_ACCEL_CTRL_REG4_A = 0x23; // 00000000   rw
LSM303_REGISTER_ACCEL_OUT_X_L_A   = 0x28;
LSM303_REGISTER_MAG_CRB_REG_M     = 0x01;
LSM303_REGISTER_MAG_MR_REG_M      = 0x02;
LSM303_REGISTER_MAG_OUT_X_H_M     = 0x03;

// Gain settings for set_mag_gain()
LSM303_MAGGAIN_1_3 = 0x20; // +/- 1.3
LSM303_MAGGAIN_1_9 = 0x40; // +/- 1.9
LSM303_MAGGAIN_2_5 = 0x60; // +/- 2.5
LSM303_MAGGAIN_4_0 = 0x80; // +/- 4.0
LSM303_MAGGAIN_4_7 = 0xA0; // +/- 4.7
LSM303_MAGGAIN_5_6 = 0xC0; // +/- 5.6
LSM303_MAGGAIN_8_1 = 0xE0; // +/- 8.1

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
