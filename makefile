objects = ../comms/nugget-api.o ../rov-core/rov-util.o ../rovlog/rovlog.o 
stdflag = -g -Wall -Wextra -L. -I. -lm -Wl,-unresolved-symbols=ignore-in-shared-libs

all :
	make accel
	make barometer
	make distance
	make probe

accel :
	gcc accel-gyro.c -o accel-gyro $(stdflag) $(objects)

barometer :
	gcc subsystem-motor.c -o subsystem-motor $(stdflag) $(objects)

distance :
	gcc distance_sensor.h -o distance_sensor $(stdflag) $(objects)

probe : 
	gcc PH_Probe.h -o PH_Probe $(stdflag) $(objects)
