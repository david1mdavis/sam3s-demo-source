/*
 * Communication.c
 *
 *  Created on: 2013-2-3
 *      Author: kren
 */
/**********************************************************
 * 				Include
 **********************************************************/
#include <stdlib.h>
#include "ad5933.h"

/***************************************************************************//**
 * @brief Initializes the I2C communication peripheral.
 *
 * @param clockFreq - I2C clock frequency (Hz).
 *                    Example: 100000 - I2C clock frequency is 100 kHz.
 * @return status - Result of the initialization procedure.
 *                  Example: 1 - if initialization was successful;
 *                           0 - if initialization was unsuccessful.
*******************************************************************************/
void I2C_Init(void)
{
    // Add your code here.
	// Initialize I2C
	I2caRegs.I2CSAR = 0x90;		//ad7414 addr //AD5933_ADDR_SLAVE;        // Slave address
	// I2CCLK = SYSCLK/(I2CPSC+1)
	#if (CPU_FRQ_40MHZ||CPU_FRQ_50MHZ)
		I2caRegs.I2CPSC.all = 4;       // Prescaler - need 7-12 Mhz on module clk
	#endif

	#if (CPU_FRQ_60MHZ)
		I2caRegs.I2CPSC.all = 6;       // Prescaler - need 7-12 Mhz on module clk
	#endif
	I2caRegs.I2CCLKL = 10;           // NOTE: must be non zero
	I2caRegs.I2CCLKH = 5;            // NOTE: must be non zero
	//I2caRegs.I2CIER.all = 0x26;      // Enable SCD & ARDY & NACK interrupts

	I2caRegs.I2CMDR.all = 0x0020;    // Take I2C out of reset
	                                 // Stop I2C when suspended

	I2caRegs.I2CFFTX.all = 0x6000;   // Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x2040;   // Enable RXFIFO, clear RXFFINT,
}

/***************************************************************************//**
 * @brief Writes data to a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes to write.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
 *
 * @return status - Number of written bytes.
*******************************************************************************/
Uint16 I2C_Write(Uint16 DestAddr, Uint16 DataValue)
{
    // Add your code here.
	I2caRegs.I2CSAR = 0x48;        // Slave address

	if(I2caRegs.I2CMDR.bit.STP == 1)
	{
		return(I2C_STP_NOT_READY_ERROR);
	}
	if(I2caRegs.I2CSTR.bit.BB == 1)
	{
		return(I2C_BUS_BUSY_ERROR);
	}
	I2caRegs.I2CCNT = 2;        // 2 addi tional  bytes  being transfe rre d
	//28035 has 4-level FIFO, so we can process up to 4 da ta one  time .
	I2caRegs.I2CDXR = DestAddr & 0xff;  	// Address should be  8 bi t
	I2caRegs.I2CDXR = DataValue & 0xff;    	// 8bit datavalue

	I2caRegs.I2CMDR.all = 0x6E20;        	// bit 14 FREE = 1
	                						// bit 13 STT = 1    (Start condition)
	                						// bit 11 STP =1    (Stop condition after transfer of bytes .)
	                						// bit 10 MST = 1    Master
	                						// bit  9 TRX = 1    Transmit
	                						// bit  5 IRS = 1 to Reset I2C bus .

	while( !( I2caRegs.I2CSTR.all & 0x0030 ) );	//XRDY && SCD
	if( I2caRegs.I2CSTR.bit.NACK == 1){
		I2caRegs.I2CMDR.bit.STP = 1;
		I2caRegs.I2CSTR.bit.NACK = 0;
	}
	return(I2C_SUCCESS);
}

/***************************************************************************//**
 * @brief Reads data from a slave device.
 *
 * @param DestAddr - Adress of the slave device.
 * @param DataValue - Pointer to a buffer that will store the received data.
 *
 * @return status - Number of read bytes.
*******************************************************************************/
Uint16 I2C_Read(Uint16 SourceAddr)
{
    // Add your code here.
	Uint16 temp;

	//g_enRD_Mode = Read_Byte ;
	if(I2caRegs .I2CMDR.bit.STP == 1)
	{
		return(I2C_STP_NOT_READY_ERROR);
	}
	if(I2caRegs.I2CSTR.bit.BB == 1)
	{
		return(I2C_BUS_BUSY_ERROR);
	}
	I2caRegs.I2CCNT = 1;
	I2caRegs.I2CDXR = SourceAddr;
	I2caRegs.I2CMDR.all = 0x6620;	//bit 14 FREE = 1
	                				//bit 13 STT = 1    (Start condition)
	               	   	   	   	   	//bit 11 STP =0    (No Stop condition after transfer of 17 bytes .)
	                				//bit 10 MST = 1    Master
	                				//bit  9 TRX = 1    Transmit
	               	   	   	   	    //bit  5 IRS = 1    to Reset I2C bus .
	DELAY_US(50);    // Delay 50us , wait
	if( 0 == SourceAddr ){
		I2caRegs.I2CCNT = 2;  			//Set up receive of 1 byte
	}
	else{
		I2caRegs.I2CCNT = 1;  			//Set up receive of 1 byte
	}

	I2caRegs.I2CMDR.all = 0x6c20;   // bit 14 FREE = 1
	               	   	   	   	   	// bit 13 STT = 1    (Re Start condition)
	                				// bit 11 STP =1    (Stop condition after transfer of bytes .)
	                				// bit 10 MST = 1    Master
	                				// bit  9 TRX = 0    Receiver
	               	   	   	   	   	// bit  5 IRS = 1 to Reset I2C bus .

	while( 0 == ( I2caRegs.I2CSTR.all & 0x2000 ) );
	while(I2caRegs.I2CFFRX.all & 0x1f00){
		temp = I2caRegs.I2CDRR;
	}

	return(temp);
}

