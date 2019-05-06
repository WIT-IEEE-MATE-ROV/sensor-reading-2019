import FaBo9Axis_MPU9250
import math
import time
import sys
import os
from collections import namedtuple

PI = math.pi
atan = math.atan
atan2 = math.atan2
sqrt = math.sqrt
sin = math.sin
cos = math.cos

mpu9250 = FaBo9Axis_MPU9250.MPU9250()
Position = namedtuple('Position', 'x y z')
Orientation = namedtuple('Orientation', 'roll pitch yaw')

pos = Position(0,0,0)

def Pitch(ACXval, ACYval, ACZval):
    pitch = 180 * atan2(ACXval, sqrt(ACYval * ACYval + ACZval * ACZval)) / 3.14
    return pitch

def Roll(ACXval, ACYval, ACZval):
    roll = 180 * atan2(ACYval, sqrt(ACXval * ACXval + ACZval * ACZval)) / 3.14
    return roll

def Yaw(MAXval, MAYval, MAZval):
    roll = Roll((accel['x']), (accel['x']), (accel['x']))
    pitch = Pitch((accel['x']), (accel['y']), (accel['z']))
    #mag_x = MAZval * sin(roll) - MAYval * cos(roll)
    #mag_y = MAXval * cos(pitch) + MAYval * sin(pitch) * sin(roll) + MAZval * sin(pitch) * cos(roll)
    #yaw = atan(mag_x/mag_y) * 180

    mag_x = MAXval * cos(pitch) + MAYval * sin(roll) * sin(pitch) + MAZval * cos(roll) * sin(pitch)
    mag_y = MAYval * cos(roll) - MAZval * sin(roll)
    yaw = 180 * atan2(-mag_y, mag_x) / 3.14;
    #yaw = atan2((-MAYval * cos(roll) + MAZval * sin(roll), MAXval * cos(pitch) + MAZval * sin(pitch) * sin(roll) + MAZval * sin(pitch) * cos(roll)) * 180/PI
    
    return yaw

while True:
    accel = mpu9250.readAccel()
    gyro = mpu9250.readGyro()
    mag = mpu9250.readMagnet()

    pitch = Pitch((accel['x']), (accel['y']), (accel['z']))
    roll = Roll((accel['x']), (accel['y']), (accel['z']))
    yaw = Yaw((mag['x']), (mag['y']), (mag['z']))

    orient = Orientation(roll, pitch, yaw)

    string = "\n== Sensor Readings ==" +\
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

