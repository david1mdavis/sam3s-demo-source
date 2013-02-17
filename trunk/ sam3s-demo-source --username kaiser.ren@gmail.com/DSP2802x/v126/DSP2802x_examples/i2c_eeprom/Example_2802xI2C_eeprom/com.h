/*
 * com.h
 *
 *  Created on: 2013-1-25
 *      Author: kren
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

#endif /* COM_H_ */
