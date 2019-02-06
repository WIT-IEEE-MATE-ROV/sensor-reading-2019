// via https://github.com/adafruit/Adafruit_Python_LSM303/blob/master/Adafruit_LSM303/LSM303.py

#ifndef LSM303_H

#define LSM303_ADDRESS_ACCEL (0x32 >> 1)  // 0011001x
#define LSM303_ADDRESS_MAG   (0x3C >> 1)  // 0011110x
                                                // Default    Type
#define LSM303_REGISTER_ACCEL_CTRL_REG1_A 0x20  // 00000111   rw
#define LSM303_REGISTER_ACCEL_CTRL_REG4_A 0x23  // 00000000   rw
#define LSM303_REGISTER_ACCEL_OUT_X_L_A   0x28
#define LSM303_REGISTER_ACCEL_OUT_X_H_A   0x29
#define LSM303_REGISTER_ACCEL_OUT_Y_L_A   0x2A
#define LSM303_REGISTER_ACCEL_OUT_Y_H_A   0x2B
#define LSM303_REGISTER_ACCEL_OUT_Z_L_A   0x2C
#define LSM303_REGISTER_ACCEL_OUT_Z_H_A   0x2D
#define LSM303_REGISTER_MAG_CRA_REG_M     0x00
#define LSM303_REGISTER_MAG_CRB_REG_M     0x01
#define LSM303_REGISTER_MAG_MR_REG_M      0x02
#define LSM303_REGISTER_MAG_OUT_X_H_M     0x03
#define LSM303_REGISTER_MAG_OUT_X_L_M     0x04
#define LSM303_REGISTER_MAG_OUT_Z_H_M     0x05
#define LSM303_REGISTER_MAG_OUT_Z_L_M     0x06
#define LSM303_REGISTER_MAG_OUT_Y_H_M     0x07
#define LSM303_REGISTER_MAG_OUT_Y_L_M     0x08

// Gain settings for set_mag_gain()
#define LSM303_MAGGAIN_1_3 0x20 // +/- 1.3
#define LSM303_MAGGAIN_1_9 0x40 // +/- 1.9
#define LSM303_MAGGAIN_2_5 0x60 // +/- 2.5
#define LSM303_MAGGAIN_4_0 0x80 // +/- 4.0
#define LSM303_MAGGAIN_4_7 0xA0 // +/- 4.7
#define LSM303_MAGGAIN_5_6 0xC0 // +/- 5.6
#define LSM303_MAGGAIN_8_1 0xE0 // +/- 8.1

struct lsm303_accel_data{
    float x;
    float y;
    float z;
};

struct lsm303_mag_data{
    float x;
    float y;
    float z;
};

#endif
