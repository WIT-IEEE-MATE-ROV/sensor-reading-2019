//https://github.com/TEConnectivity/MS5837_Generic_C_Driver/blob/master/ms5837.c

#include <stdio.h>
#include <wiringPiI2C.h>
#include "ms5837.h"

/**
  * The header "i2c.h" has to be implemented for your own platform to 
  * conform the following protocol :
  *
  * enum i2c_transfer_direction {
  * 	I2C_TRANSFER_WRITE = 0,
  * 	I2C_TRANSFER_READ  = 1,
  * };
  * 
  * enum status_code {
  * 	STATUS_OK           = 0x00,
  * 	STATUS_ERR_OVERFLOW	= 0x01,
  *		STATUS_ERR_TIMEOUT  = 0x02,
  * };
  * 
  * struct i2c_master_packet {
  * 	// Address to slave device
  * 	uint16_t address;
  * 	// Length of data array
  * 	uint16_t data_length;
  * 	// Data array containing all data to be transferred
  * 	uint8_t *data;
  * };
  * 
  * void i2c_master_init(void);
  * enum status_code i2c_master_read_packet_wait(struct i2c_master_packet *const packet);
  * enum status_code i2c_master_write_packet_wait(struct i2c_master_packet *const packet);
  * enum status_code i2c_master_write_packet_wait_no_stop(struct i2c_master_packet *const packet);
  */

#include "i2c.h"

#ifdef __cplusplus
extern "C" {
#endif
  

// Static functions
static enum ms5837_status ms5837_write_command(uint8_t);
static enum ms5837_status ms5837_read_eeprom_coeff(uint8_t, uint16_t*);
static enum ms5837_status ms5837_read_eeprom(void);
static enum ms5837_status ms5837_conversion_and_read_adc( uint8_t, uint32_t *);
static bool ms5837_crc_check (uint16_t *n_prom, uint8_t crc);

enum ms5837_resolution_osr ms5837_resolution_osr;
static uint16_t eeprom_coeff[MS5837_COEFFICIENT_NUMBERS+1];
static uint32_t conversion_time[6] = {	MS5837_CONVERSION_TIME_OSR_256,
					MS5837_CONVERSION_TIME_OSR_512,
					MS5837_CONVERSION_TIME_OSR_1024,
					MS5837_CONVERSION_TIME_OSR_2048,
					MS5837_CONVERSION_TIME_OSR_4096,
					MS5837_CONVERSION_TIME_OSR_8192};

// Default value to ensure coefficients are read before converting temperature  
bool ms5837_coeff_read = false;

/**
 * \brief Configures the SERCOM I2C master to be used with the MS5837 device.
 */
void ms5837_init(void)
{
	ms5837_resolution_osr = ms5837_resolution_osr_8192;
	
    /* Initialize and enable device with config. */
	i2c_master_init();
}

  
/**
 * \brief Check whether MS5837 device is connected
 *
 * \return bool : status of MS5837
 *       - true : Device is present
 *       - false : Device is not acknowledging I2C address
  */
bool ms5837_is_connected(void)
{
	enum status_code i2c_status;
	
	struct i2c_master_packet transfer = {
		.address     = MS5837_ADDR,
		.data_length = 0,
		.data        = NULL,
	};
	/* Do the transfer */
	i2c_status = i2c_master_write_packet_wait(&transfer);
	if( i2c_status != STATUS_OK)
		return false;
	
	return true;
}
	
  

//not really sure if this works
float getTemp(int fd) {
  float init = wiringPiI2CRead(fd);
  return init;
  
  /* the data sheet conversions 
  https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=MS5837-02BA01&DocType=Data+Sheet&DocLang=English&DocFormat=pdf&PartCntxt=CAT-BLPS0059
  
  */
  
}

int main() {
  int fd = wiringPiI2CSetup(); //need device ID, use i2cdetect when sensor is connected to Rasp Pi
  printf("%.2f\n", getTemp(fd));
  return 0;
}

//convert temp to requested units, default is Centigrade
float convertTemp(int fd, conversion=UNITS_Centigrade){
  float temp = getTemp(fd);
  float degC = (temp/100.0);
  if (conversion == UNITS_Farenheit)
    return ((9/5) * degC +32);
  else if (conversion == UNITS_Kelvin) 
    return (degC - 372);
  return degC;
}

//conversions from data sheet
float calculate(int fd){
  float OFFi = 0;
  float SENSi = 0;
  float Ti = 0;
  
  
  
}
  

  
