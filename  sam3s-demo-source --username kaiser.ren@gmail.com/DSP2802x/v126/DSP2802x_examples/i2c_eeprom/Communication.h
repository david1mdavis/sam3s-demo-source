/*
 * Communication.h
 *
 *  Created on: 2012-11-26
 *      Author: cui
 */
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/

/******************************************************************************/
/* Functions Prototypes                                                       */
/******************************************************************************/

/*! Initializes the I2C communication peripheral. */
void I2C_Init(void);

/*! Writes data to a slave device. */
Uint16 I2C_Write(unsigned char DestAddr, unsigned char DataValue);

/*! Reads data from a slave device. */
unsigned char I2C_Read(unsigned char SourceAddr);

#endif // _COMMUNICATION_H_
