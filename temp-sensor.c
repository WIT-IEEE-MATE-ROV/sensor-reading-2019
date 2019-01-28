#include <stdio.h>
#include <wiringPiI2C.h>

float getTemp(int fd) {
  int init = wiringPiI2CRead(fd);
}

int main() {
  int fd = wiringPiI2CSetup(); //need device ID, use i2cdetect when sensor is connected to Rasp Pi
  printf("%.2f\n", getTemp(fd));
  return 0;
}
