task main()
{
  while (true)
  {
    //Make sure the value is not an error
    if(SensorValue[ultrasonic] > 0)
    {
      if (SensorValue[ultrasonic] <= 7) {
        //there is something within the threshold range
        motor[leftServo] = -50;
        motor[rightServo] = 50;
        wait1Msec(800);
        } else {
        //nothing in the threshold range
        motor[leftServo] = 50;
        motor[rightServo] = 50;
      }
    }
  }
}
// Source: http://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Use_Ultrasonic_Sensor_To_Avoid_Walls
