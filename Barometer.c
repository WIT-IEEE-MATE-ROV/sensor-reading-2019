//https://github.com/TEConnectivity/MS5837_Generic_C_Driver/blob/master/ms5837.c
//https://github.com/bluerobotics/ms5837-python/blob/master/ms5837.py

#include <stdio.h>
#include <unistd.h>
#include "./WiringPi/wiringPi/wiringPiI2C.h"
#include "ms5837.h"

//pass one of the defined densities (i.e. DENSITY_FRESHWATER or DENSITY_SALTWATER)
void setFluidDensity(struct ms5837_data *data, int density){
	data->fluidDensity = density;
}
	
//Pressure in requested units
float pressure(struct ms5837_data *data, float conversion){
	return data->pressure * conversion;	
}
	
//convert temp to requested units, default is Celsius
float temperature(struct ms5837_data *data, int conversion){
  float degC = (data->temp/100.0);
  if (conversion == UNITS_Farenheit)
    return ((9/5) * degC +32);
  else if (conversion == UNITS_Kelvin) 
    return (degC - 372);
  return degC;
}
	
// Depth relative to MSL pressure in given fluid density
float depth(struct ms5837_data *data){
  setFluidDensity(data, DENSITY_FRESHWATER);
	return (pressure(data, UNITS_PA)-101300.0)/(data->fluidDensity*9.80665);
}

// Altitude relative to MSL pressure
float altitude(struct ms5837_data *data){
	return (1-pow((pressure(data, UNITS_mbar)/1013.25),.190284))*145366.45*.3048;
}

// via datasheet
void calculate(struct ms5837_data *data) {
	int32_t dT;
  int64_t OFF, SENS;
  uint64_t OFFi, SENSi, Ti;

	dT = data->d2 - data->C[5]*256;
	SENS = data->C[1]*65536+(data->C[3]*dT)/128;
	OFF = data->C[2]*131072+(data->C[4]*dT)/64;
	data->pressure = (data->d1*SENS/(2097152)-OFF)/(32768);
	data->temp = 2000+dT*data->C[6]/8388608;
		
	// Second order compensation
	if ((data->temp/100) < 20) { // Low temp
			Ti = (11*dT*dT)/(34359738368);
			OFFi = (31*(data->temp-2000)*(data->temp-2000))/8;
			SENSi = (63*(data->temp-2000)*(data->temp-2000))/32;
	}
	
	OFF -= OFFi;
	SENS -= SENSi;
		
	data->temp = (float)(data->temp-Ti);
	data->pressure = (float)(((data->d1*SENS)/2097152-OFF)/32768)/100.0;
}

//TODO fix d array
void ms5837_read(struct ms5837_data *data, uint32_t oversampling){
  	uint16_t d[3];
	//read temp
	wiringPiI2CWrite(MS5837_ADDR, MS3857_START_TEMPERATURE_ADC_CONVERSION + 2*oversampling);
	sleep(0.000025*pow(2,8+oversampling));
	d = wiringPiI2CRead(MS5837_ADDR);
	data->d1 = d[0] << 16 | d[1] << 8 | d[2];
	//read pressure
	wiringPiI2CWrite(MS5837_ADDR, MS3857_START_PRESSURE_ADC_CONVERSION + 2*oversampling);
	sleep(0.000025*pow(2,8+oversampling));
	d = wiringPiI2CRead(MS5837_ADDR);
	data->d2 = d[0] << 16 | d[1] << 8 | d[2];
	calculate(data);
	printf("Temperature: %0.2f C\n", temperature(data, UNITS_Celsius));
	printf("Pressure: %0.2f psi\n", pressure(data, UNITS_psi));
	printf("Depth: %0.2f", depth(data));
	printf("Altitude: %0.2f", altitude(data));
}
	
// copied from TEConnectivity code
bool crc_check(struct ms5837_data *data, uint8_t crc){
	uint8_t cnt, n_bit;
	uint16_t n_rem, crc_read;
	n_rem = 0x00;
	crc_read = data->n_prom[0];
	data->n_prom[MS5837_COEFFICIENT_NUMBERS] = 0;
	data->n_prom[0] = (0x0FFF & (data->n_prom[0]));    // Clear the CRC byte

	for(cnt = 0 ; cnt < (MS5837_COEFFICIENT_NUMBERS+1)*2 ; cnt++) {

		// Get next byte
		if (cnt%2 == 1)
			n_rem ^=  data->n_prom[cnt>>1] & 0x00FF;
		else
			n_rem ^=  data->n_prom[cnt>>1]>>8;

		for( n_bit = 8; n_bit > 0 ; n_bit-- ){

			if( n_rem & 0x8000 )
				n_rem = (n_rem << 1) ^ 0x3000;
			else
				n_rem <<= 1;
		}
	}
	n_rem >>= 12;
	data->n_prom[0] = crc_read;
	
	return  ( n_rem == crc );	
}

/**
Configures the SERCOM I2C master to be used with the MS5837 device.
 */
void ms5837_init(struct ms5837_data *data){
    /* Initialize and enable device with config. */
	wiringPiI2CSetup(MS5837_ADDR);
	wiringPiI2CWrite(MS5837_ADDR, MS5837_RESET);
	
	// Read calibration values and CRC
	for (int i=0;i<8;i++){
		uint32_t c = wiringPiI2CRead8(MS5837_ADDR, MS5837_PROM_READ + 2*i);
		c = ((c & 0xFF) << 8) | (c >> 8);
		data->C[i] = c;
	}
	
	//Check crc
	uint8_t crc = (data->C[0] & 0xF000) >> 12;
	if (!crc_check(data, crc))
		printf("PROM read error, CRC failed.");
}

int main(void) {
	uint32_t oversampling = OSR_8192; //choose
	struct ms5837_data data;
 	ms5837_init(&data);
	while(true){
		ms5837_read(&data, oversampling);
	}
}
