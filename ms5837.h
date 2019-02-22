/*
temp sensor driver header file
*/

#ifndef MS5837_H_INCLUDED
#define MS5837_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

//constants

//kg/m^3 convenience
#define DENSITY_FRESHWATER 997
#define DENSITY_SALTWATER 1029

//conversion factors (native unit - mbar)
#define UNITS_PA 	100.0
#define UNITS_hPa 	1.0
#define UNITS_kPa 	0.1
#define UNITS_mbar 	1.0
#define UNITS_bar 	0.001
#define UNITS_atm 	0.000986923
#define UNITS_Torr 	0.750062
#define UNITS_psi 	0.014503773773022

//Valid units
#define UNITS_Celsius 	 1
#define UNITS_Farenheit  2
#define UNITS_Kelvin     3

// Oversampling options
#define OSR_256  0
#define OSR_512  1
#define OSR_1024 2
#define OSR_2048 3
#define OSR_4096 4
#define OSR_8192 5

//I2C addresses/registers
#define MS5837_ADDR           				        0x76
#define MS5837_RESET           				        0x1E
#define MS5837_ADC_READ        				        0x00
#define MS5837_PROM_READ      			 	        0xA0
#define MS3857_START_PRESSURE_ADC_CONVERSION  		0x4A //depends on what ORS is chosen (this is for ORS=8192)
#define MS3857_START_TEMPERATURE_ADC_CONVERSION 	0x5A //depends on what ORS is chosen (this is for ORS=8192)

#define MS5837_CONVERSION_OSR_MASK				    0x0F

#define MS5837_CONVERSION_TIME_OSR_256				1000
#define MS5837_CONVERSION_TIME_OSR_512				2000
#define MS5837_CONVERSION_TIME_OSR_1024				3000
#define MS5837_CONVERSION_TIME_OSR_2048				5000
#define MS5837_CONVERSION_TIME_OSR_4096				9000
#define MS5837_CONVERSION_TIME_OSR_8192				17000

// MS5837 commands
#define MS5837_PROM_ADDRESS_READ_ADDRESS_0			0xA0
#define MS5837_PROM_ADDRESS_READ_ADDRESS_1			0xA2
#define MS5837_PROM_ADDRESS_READ_ADDRESS_2			0xA4
#define MS5837_PROM_ADDRESS_READ_ADDRESS_3			0xA6
#define MS5837_PROM_ADDRESS_READ_ADDRESS_4			0xA8
#define MS5837_PROM_ADDRESS_READ_ADDRESS_5			0xAA
#define MS5837_PROM_ADDRESS_READ_ADDRESS_6			0xAC
#define MS5837_PROM_ADDRESS_READ_ADDRESS_7			0xAE

// Coefficients indexes for temperature and pressure computation
#define MS5837_CRC_INDEX							        0
#define MS5837_PRESSURE_SENSITIVITY_INDEX					1
#define MS5837_PRESSURE_OFFSET_INDEX						2
#define MS5837_TEMP_COEFF_OF_PRESSURE_SENSITIVITY_INDEX		3
#define MS5837_TEMP_COEFF_OF_PRESSURE_OFFSET_INDEX			4
#define MS5837_REFERENCE_TEMPERATURE_INDEX					5
#define MS5837_TEMP_COEFF_OF_TEMPERATURE_INDEX				6
#define MS5837_COEFFICIENT_NUMBERS				    		7

struct ms5837_data {
	float fluidDensity;
	float pressure;
	float temp;
  unsigned short d1, d2;
	unsigned short n_prom[16], C[7]; // calibration values
};

#endif /* MS5837_H_INCLUDED */

