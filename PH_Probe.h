// serial ports. Edit pins as needed for your setup.
Serial phSensor(txPin, rxPin);
Serial pc(USBTX,USBRX);
 
// echo the data to the PC serial port
bool echoToPC = true;
 
// input buffer.
char dataIn[20];
int dataInCount = 0;
 
// the pH we got and a flag to indicate a new value. Volatile to ensure the main loop sees new values.
volatile float phReading = 0;
volatile bool gotReading = false;
 
// on data from the sensor
void onDataRx() {
  while (phSensor.readable()) { // while there is data
 
    dataIn[dataInCount] = phSensor.getc(); // read it
    if (echoToPC) // echo to the PC if enabled
      pc.putc(dataIn[dataInCount];
 
    if (dataIn[dataInCount] == 13) { // if the end of line character
      dataIn[dataInCount] = 0; // change it to a null (standard c string termination indicator)
      phReading = atof(dataIn);  // convert the string into a number
      gotReading = true;   // flag the data as being new.
    } else {                      // not the end of a line
      dataInCount++;         // increase the counter
      if (dataInCount == 20)  // check we haven't run out of buffer.
        dataInCount = 0;
    } 
 
  } // end of while there is data waiting loop
}
 
// send the stop auto command
void stopAutoReading() {
  phSensor.putc('e');
  phSensor.putc(13);
}
 
// send the start auto command
void startAutoReading() {
  phSensor.putc('c');
  phSensor.putc(13);
}
 
// calibrate to a pH of 7 (change to f for a pH of 4 or t for a pH of 10)
void calibratepH7() {
  stopAutoReading();
  phSensor.putc('s');
  phSensor.putc(13);
}
 
// calibrate to a pH of 7 (change to f for a pH of 4 or t for a pH of 10)
void calibratepH7() {
  stopAutoReading();
  phSensor.putc('s');
  phSensor.putc(13);
}
 
 
 
// do a single read
void readpH() {
  phSensor.putc('R');
  phSensor.putc(13);
}
 
// set the sensor LED state
void sensorLED(bool on) {
  phSensor.putc('L');
  if (on)
    phSensor.putc('1');
  else
    phSensor.putc('0');
 
  phSensor.putc(13);
}
 
 
int main () {
 
  // set the serial baud rates
  phSensor.baud(38400);
  pc.baud(38400); // change as needed
 
  wait(1); // wait for the sensor to start up.
 
  phSensor.attach(&onDataRx); // call the RX function whenever we get data.
 
  // get the sensor info
  echoToPC = true; 
  getSensorInfo();
  wait(1);
 
  // stop direct echoing of the sensor output (comment this line out for debugging maybe
  echoToPC = false;
 
  // clear the flag 
  gotReading = false;
 
  // make sure we start at the front of the buffer just in case the info line didn't end in a carriage return for some reason.
  dataInCount = 0;
 
  // set the sensor running
  startAutoReading();
 
  while (1) {  // loop forever
 
    if (gotReading) {   // if there is a new reading
      pc.printf("pH = %.1f\n",phReading);  // print it out.
      gotReading = false;
    }
  }
 
}
 
 //Source: https://os.mbed.com/forum/mbed/topic/3895/
              
              
              
              
              
              
              
