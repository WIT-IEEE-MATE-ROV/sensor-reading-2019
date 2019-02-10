objects = ../comms/nugget-api.o ../rov-core/rov-util.o ../rovlog/rovlog.o 
stdflag = -g -Wall -Wextra -L. -I. -lm -Wl,-unresolved-symbols=ignore-in-shared-libs

all :
	make accel-gyro
	make distance
	make bar02
	make probe

accel-gyro :
	gcc accel-gyro.c -o accel-gyro $(stdflag) $(objects)

distance :
	gcc distance_sensor.c -o distance_sensor $(stdflag) $(objects)

bar02 :
	gcc temp-sensor.c -o temp-sensor $(stdflag) $(objects)

probe :
	gcc PH_probe.c -o PH_probe $(stdflag) $(objects)

