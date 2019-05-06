import math
import FaBo9Axis_MPU9250
import time
import sys

mpu9250 = FaBo9Axis_MPU9250.MPU9250()

atan2 = math.atan2
sqrt = math.sqrt
sin = math.sin
cos = math.cos



def Read():
    accel = mpu9250.readAccel()
    print
    " ax = ", (accel['x'])
    print
    " ay = ", (accel['y'])
    print
    " az = ", (accel['z'])

    gyro = mpu9250.readGyro()
    print
    " gx = ", (gyro['x'])
    print
    " gy = ", (gyro['y'])
    print
    " gz = ", (gyro['z'])

    mag = mpu9250.readMagnet()
    print
    " mx = ", (mag['x'])
    print
    " my = ", (mag['y'])
    print
    " mz = ", (mag['z'])
    print

    time.sleep(0.5)

def ACX():
    accel = mpu9250.readAccel()
    ACXval = (accel['x'])
    return ACXval

def ACY():
    accel = mpu9250.readAccel()
    ACYval = (accel['y'])
    return ACYval

def ACZ():
    accel = mpu9250.readAccel()
    ACZval = (accel['z'])
    return ACZval

def GRX():
    gyro = mpu9250.readGyro()
    GRXval = (gyro['x'])
    return GRXval
def GRY():
    gyro = mpu9250.readGyro()
    GRYval =  (gyro['y'])
    return GRYval
def GRZ():
    gyro = mpu9250.readGyro()
    GRZval = (gyro['z'])
    return GRZval

def MAX():
    mag = mpu9250.readMagnet()
    MAXval = (mag['x'])
    return MAXval

def MAY():
    mag = mpu9250.readMagnet()
    MAYval = (mag['y'])
    return MAYval

def MAZ():
    mag = mpu9250.readMagnet()
    MAZval = (mag['z'])
    return MAZval

def Pitch():
    ACXval = ACX()
    ACYval = ACY()
    ACZval = ACZ()
    pitch = 180 * atan2(ACXval, sqrt(ACYval * ACYval + ACZval * ACZval)) / 3.14
    return pitch

def Roll():
    ACXval = ACX()
    ACYval = ACY()
    ACZval = ACZ()
    roll = 180 * atan2(ACYval, sqrt(ACXval * ACXval + ACZval * ACZval)) / 3.14
    return roll

def Yaw():
    roll = Roll()
    pitch = Pitch()
    MAXval = MAX()
    MAYval = MAY()
    MAZval = MAZ()
    mag_x = MAXval * cos(pitch) + MAYval * sin(roll) * sin(pitch) + MAZval * cos(roll) * sin(pitch)
    mag_y = MAYval * cos(roll) - MAZval * sin(roll)
    yaw = 180 * atan2(-mag_y, mag_x) / 3.14;
    return yaw

