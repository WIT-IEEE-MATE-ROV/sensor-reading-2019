import mpu6050
sensor = mpu6050(0x68)

class mpu6050:

    def get_accel_x(self):
        return sensor.get_accel_data().x

    def get_accel_y(self):
        return sensor.get_accel_data().y

    def get_accel_z(self):
        return sensor.get_accel_data().z

    def get_gyro_x(self):
        return sensor.get_gyro_data().x

    def get_gyro_y(self):
        return sensor.get_gyro_data().y

    def get_gyro_z(self):
        return sensor.get_gyro_data().z


if __name__ == "__main__":
    print(" Acceleration X |{:d}".format(mpu6050.get_accel_x()))
    print(" Acceleration Y |{:d}".format(mpu6050.get_accel_y()))
    print(" Acceleration Z |{:d}".format(mpu6050.get_accel_z()))
    print(" Gyroscope X    |{:d}".format(mpu6050.get_gyro_x()))
    print(" Gyroscope Y    |{:d}".format(mpu6050.get_gyro_y()))
    print(" Gyroscope Z    |{:d}".format(mpu6050.get_gyro_z()))
