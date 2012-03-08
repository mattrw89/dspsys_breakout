#ifndef LIB_I2C_H_
#define LIB_I2C_H_

#include <stdint.h>
#include "inc/lm3s8962.h"
//#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
//#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"

void I2CInit();
void I2CSendData( uint8_t slave_address, char *ptr_data, uint8_t length); 
	
#endif /*LIB_I2C_H_*/
