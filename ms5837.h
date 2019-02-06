/*
temp sensor driver header file
*/

#ifndef MS5837_H_INCLUDED
#define MS5837_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

//kg/m^3 convenience
DENSITY_FreSHWATER = 997
DENSITY_SALTWATER = 1029

//conversion factors (native unit - mbar)
UNITS_PA = 100.0
UNITS_hPa = 1.0
UNITS_kPa = 0.1
UNITS_mbar = 1.0
UNITS_bar = 0.001
UNITS_atm = 0.000986923
UNITS_Torr = 0.750062
UNITS_psi = 0.014503773773022

//Valid units
UNITS_Centigrade = 1
UNITS_Farenheit = 2
UNITS_Kelvin = 3

//I2C addresses/registers
_MS5837_ADDR            = 0x76
_MS5837_RESET           = 0x1E
_MS5837_ADC_READ        = 0x00
_MS5837_PROM_READ       = 0xA0
_MS3857_CONVERT_D1_256  = 0x40
_MS3857_CONVERT_D2_265  = 0x50

enum ms5837_resolution_osr {
	ms5837_resolution_osr_256 = 0,
	ms5837_resolution_osr_512,
	ms5837_resolution_osr_1024,
	ms5837_resolution_osr_2048,
	ms5837_resolution_osr_4096,
	ms5837_resolution_osr_8192
};

enum ms5837_status {
	ms5837_status_ok,
	ms5837_status_no_i2c_acknowledge,
	ms5837_status_i2c_transfer_error,
	ms5837_status_crc_error
};
	
// Functions

/**
 * \brief Configures the SERCOM I2C master to be used with the ms5837 device.
 */
void ms5837_init(void);

/**
 * \brief Check whether MS5837 device is connected
 *
 * \return bool : status of MS5837
 *       - true : Device is present
 *       - false : Device is not acknowledging I2C address
  */
bool ms5837_is_connected(void);

/**
 * \brief Reset the MS5837 device
 *
 * \return ms5837_status : status of MS5837
 *       - ms5837_status_ok : I2C transfer completed successfully
 *       - ms5837_status_i2c_transfer_error : Problem with i2c transfer
 *       - ms5837_status_no_i2c_acknowledge : I2C did not acknowledge
 */
enum ms5837_status ms5837_reset(void);

/**
 * \brief Set  ADC resolution.
 *
 * \param[in] ms5837_resolution_osr : Resolution requested
 *
 */
void ms5837_set_resolution(enum ms5837_resolution_osr );

/**
 * \brief Reads the temperature and pressure ADC value and compute the compensated values.
 *
 * \param[out] float* : Celsius Degree temperature value
 * \param[out] float* : mbar pressure value
 *
 * \return ms5837_status : status of MS5837
 *       - ms5837_status_ok : I2C transfer completed successfully
 *       - ms5837_status_i2c_transfer_error : Problem with i2c transfer
 *       - ms5837_status_no_i2c_acknowledge : I2C did not acknowledge
 *       - ms5837_status_crc_error : CRC check error on on the PROM coefficients
 */
enum ms5837_status ms5837_read_temperature_and_pressure(float *, float *);

#endif /* MS5837_H_INCLUDED */
  
