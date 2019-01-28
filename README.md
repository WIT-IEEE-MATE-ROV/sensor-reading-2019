# sensor-reading
For reading the sensors on the ROV and making nice, happy interfaces for them.

For PH probe:
The PH probe is giving off a current that is generated from the hydrogen ion activity
This number is the reciprocal of that activity and can be perdicted with this equation
E = E^0 - (2.303RT/F)pH; R = ideal gas constant, T= temp in Kelvin, F = Faraday constant

says for connecting: either SMA cable to SMA breakout board or Female BNC and BNC to SMA adapter
Just outputs a number
Takes time to get an accurate reading 

reading I2c inputs in Pi using C step by step
https://www.instructables.com/id/Reading-I2C-Inputs-in-Raspberry-Pi-using-C/


For temp sensor:


Something similair using I2C and Pi but diff temp sensor
https://www.instructables.com/id/Reading-I2C-Inputs-in-Raspberry-Pi-using-C/
used Librarys: stdio, stdlib, string, stdint

helpful I2C functions:
https://raspberry-projects.com/pi/programming-in-python/i2c-programming-in-python/using-the-i2c-interface-2

helpful I2C example:
https://raspberry-projects.com/pi/programming-in-python/i2c-programming-in-python/using-the-i2c-interface-2

I2C installation for Pi- step by step guide:
http://skpang.co.uk/blog/archives/575

Pi over I2C in C
http://skpang.co.uk/blog/archives/575

WiringPi:http://wiringpi.com/

  - about: https://projects.drogon.net/raspberry-pi/wiringpi/
  - functions: https://projects.drogon.net/raspberry-pi/wiringpi/functions/
  - pins: https://projects.drogon.net/raspberry-pi/wiringpi/pins/
      -Pin 3 - I2C.1 SDA
      -Pin 5: I2C.1 SCL
      -Pin 27: I2C.0 ID SDA
      Pin 28: I2C.0 ID SCL
  - Using I2C with wiringPi: https://projects.drogon.net/raspberry-pi/wiringpi/i2c-library/ and https://learn.sparkfun.com/tutorials/raspberry-pi-spi-and-i2c-tutorial/all
