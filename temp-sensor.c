#include <stdio.h>
#include <wiringPiI2C.h>
#include "ms5837.h"

//not really sure if this works
float getTemp(int fd) {
  float init = wiringPiI2CRead(fd);
  return init;
  
  /* the data sheet conversions 
  https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=MS5837-02BA01&DocType=Data+Sheet&DocLang=English&DocFormat=pdf&PartCntxt=CAT-BLPS0059
  
  */
  
}

int main() {
  int fd = wiringPiI2CSetup(); //need device ID, use i2cdetect when sensor is connected to Rasp Pi
  printf("%.2f\n", getTemp(fd));
  return 0;
}

//convert temp to requested units, default is Centigrade
float convertTemp(int fd, conversion=UNITS_Centigrade){
  float temp = getTemp(fd);
  float degC = (temp/100.0);
  if (conversion == UNITS_Farenheit)
    return ((9/5) * degC +32);
  else if (conversion == UNITS_Kelvin) 
    return (degC - 372);
  return degC;
}

  
