/*
 * com.h
 *
 *  Created on: 2012-11-26
 *      Author: cui
 */

#ifndef COM_H_
#define COM_H_

#include <stdlib.h>

/**********************************************************
 * 				prototype
 **********************************************************/
// Prototype statements for functions found within this file.
void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);
Uint16 scia_read(void);
void scia_Byte2Hex( unsigned char byte);
void scia_PrintLF( void );
#endif /* COM_H_ */
