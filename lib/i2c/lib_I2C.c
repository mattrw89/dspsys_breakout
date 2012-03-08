#include "lib_I2C.h"
#include <stdint.h>

//-----------------------------------------------------------------------------------
void I2CInit() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    
    GPIOPinConfigure(GPIO_PB2_I2C0SCL); //PB2 = SCL = gn
	GPIOPinConfigure(GPIO_PB3_I2C0SDA); //PB3 = SDA = bl
	
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3);


	I2CMasterInitExpClk(I2C0_MASTER_BASE, SysCtlClockGet(), false); // Initialize the master module, set clock/data speed
}

//-----------------------------------------------------------------------------------

void I2CSendData( uint8_t slave_address, char *ptr_data, uint8_t length) {
	
	slave_address = slave_address >> 1;			//Stellaris needs the shifted address
	I2CMasterSlaveAddrSet(I2C0_MASTER_BASE, slave_address, false);	//sets up the clock along with the slave address
	
	if(length == 1){		//determines if single send or burst is needed
		I2CMasterDataPut(I2C0_MASTER_BASE, *ptr_data);  //loads data into buffer
		I2CMasterControl(I2C0_MASTER_BASE, I2C_MASTER_CMD_SINGLE_SEND); //initailizes the the send command
		while(I2CMasterBusy(I2C0_MASTER_BASE)) {}		//waits for i2c bus to no longer be busy
	}
	
	else{					
		I2CMasterDataPut(I2C0_MASTER_BASE, *ptr_data);	//loads data into buffer
		I2CMasterControl(I2C0_MASTER_BASE, I2C_MASTER_CMD_BURST_SEND_START); //begins the burst chain of commands
		while(I2CMasterBusy(I2C0_MASTER_BASE)) {}		//waits for i2c bus to no longer be busy
		length--;		//indicates how much information is left to send
		ptr_data += sizeof(uint8_t); //increase the pointer to the next byte of data
		
		for(; length > 1; length--){
			I2CMasterDataPut(I2C0_MASTER_BASE, *ptr_data); 
			I2CMasterControl(I2C0_MASTER_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);  //continues the I2C transmit
			while(I2CMasterBusy(I2C0_MASTER_BASE)) {}
			ptr_data += sizeof(uint8_t);
		}
		I2CMasterDataPut(I2C0_MASTER_BASE, *ptr_data);
		I2CMasterControl(I2C0_MASTER_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);	//finishes the I2C transmit
		while(I2CMasterBusy(I2C0_MASTER_BASE)) {}		
	}
}
