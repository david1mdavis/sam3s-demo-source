/*
 * Communication.h
 *
 *  Created on: 2013-2-3
 *      Author: kren
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
Uint16 I2C_Write(Uint16 slaveAddress, Uint16 dataBuffer);

/*! Reads data from a slave device. */
Uint16 I2C_Read(Uint16 SourceAddr);

#endif // _COMMUNICATION_H_
