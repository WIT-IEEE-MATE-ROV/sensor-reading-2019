import time
import sys
import Acc_Lib as AC
import FaBo9Axis_MPU9250
x=1
mpu9250 = FaBo9Axis_MPU9250.MPU9250()
while x == 1 :
  GRX = AC.GRX()
  GRY = AC.GRY()
  GRZ = AC.GRZ()
  MAX = AC.MAX()
  MAY = AC.MAY()
  MAZ = AC.MAZ()
  Pitch = AC.Pitch()
  Roll = AC.Roll()
  Yaw = AC.Yaw()
  #print ("your roll is = ", Roll)
  #time.sleep(1)
  #print ("your Pitch is = ", Pitch)
  #time.sleep(1)
  #print ("your YAW is = " , Yaw)
  print("your MAX is = ", MAX)
  print("your MAY is = " ,MAY)
  print("your MAZ is = ", MAZ)
  print("your GRX is = ", GRX)
  print("your GRY is = ", GRY)
  print("your GRZ is = ", GRZ)
  time.sleep(.5)
