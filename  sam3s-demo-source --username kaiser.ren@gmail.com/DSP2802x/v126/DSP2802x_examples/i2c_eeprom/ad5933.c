/*
 * ad5933.c
 *
 *  Created on: 2013-1-24
 *      Author: kren
 */
/**********************************************************
 * 				Include
 **********************************************************/
#include "ad5933.h"

/**********************************************************
 * 				Macro
 **********************************************************/

/**********************************************************
 * 				Global Variable
 **********************************************************/

/**********************************************************
 * 				function
 **********************************************************/
/**
 * ad5933 initialization
 */
void ad5933_init(void)
{
}

/*
 * ad5933 mode switch
 */
void ad5933_mode(ad5933_state_t state)
{
}

/*
 * ad5933 status read.
 */
uint8_t ad5993_status(void)
{
	//setup address pointer
	I2CA_Write( (AD5933_ADDR_SLAVE << 1) | 0x00);	//slave address, WR
	I2CA_Write( AD5933_CMD_CODE_ADDRS_PTR);			//address pointer
	I2CA_Write( AD5933_ADDR_STAT_REG_MSB);			//address pointer

	//read status
	I2CA_Write( (AD5933_ADDR_SLAVE << 1) | 0x01);	//slave address, RD
	return (I2CA_Read());
}


//eof
