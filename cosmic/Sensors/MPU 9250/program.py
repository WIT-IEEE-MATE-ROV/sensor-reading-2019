import FaBo9Axis_MPU9250
import time
import sys
import os
from collections import namedtuple

mpu9250 = FaBo9Axis_MPU9250.MPU9250()
Position = namedtuple('Position', 'x y z')
Orientation = namedtuple('Orientation', 'roll pitch yaw')

pos = Position(0,0,0)
orient = Orientation(0,0,0)
while True:
    accel = mpu9250.readAccel()
    gyro = mpu9250.readGyro()
    mag = mpu9250.readMagnet()

    string = "== Sensor Readings =="+\
    "\n-- Accelerometer --" +\
    "\n ax = {:f} ".format( accel['x'] ) +\
    "\n ay = {:f} ".format( accel['y'] ) +\
    "\n az = {:f} ".format( accel['z'] ) +\
    "\n-- Gyroscope --"+\
    "\n gx = {:f} ".format( gyro['x'] )+\
    "\n gy = {:f} ".format( gyro['y'] )+\
    "\n gz = {:f} ".format( gyro['z'] )+\
    "\n-- Magnetometer --"+\
    "\n mx = {:f} ".format( mag['x'] )+\
    "\n my = {:f} ".format( mag['y'] )+\
    "\n mz = {:f} ".format( mag['z'] )+\
    "\n\n== Derived Values =="+\
    "\n-- Position --"+\
    "\n px = {:f}".format( pos.x )+\
    "\n py = {:f}".format( pos.y )+\
    "\n pz = {:f}".format( pos.z )+\
    "\n-- Orientation --"+\
    "\n pr = {:f}".format( orient.roll )+\
    "\n pp = {:f}".format( orient.pitch )+\
    "\n py = {:f}".format( orient.yaw )

    os.system('clear')
    print(string)
    time.sleep(0.1)

