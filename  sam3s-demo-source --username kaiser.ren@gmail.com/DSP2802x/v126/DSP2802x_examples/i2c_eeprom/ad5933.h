/*
 * ad5933.h
 *
 *  Created on: 2013-1-24
 *      Author: kren
 */

#ifndef AD5933_H_
#define AD5933_H_

/**********************************************************
 * 				Macro
 **********************************************************/
#define AD5933_ADDR_CTRL_REG_MSB	0x80	//control reg addr msb
#define AD5933_ADDR_CTRL_REG_LSB	0x81	//control reg addr lsb

#define AD5933_ADDR_FREQ_REG_MSB  	0x82	//start frequency reg addr 1st
#define AD5933_ADDR_FREQ_REG_MMB	0x83	//start frequency reg addr 2nd
#define AD5933_ADDR_FREQ_REG_LSB	0x84	//start frequency reg addr 3rd

#define AD5933_ADDR_FICT_REG_MSB	0x85	//freq increment reg addr 1st
#define AD5933_ADDR_FICT_REG_MMB	0x86	//freq increment reg addr 2ne
#define AD5933_ADDR_FICT_REG_LSB	0x87 	//freq increment reg addr 3rd

#define AD5933_ADDR_NICT_REG_MSB	0x88	//number of increment addr msb
#define AD5933_ADDR_NICT_REG_LSB	0x89	//number of increment addr lsb

#define AD5933_ADDR_STCY_REG_MSB	0x8a	//number of settling time cycle addr msb
#define AD5933_ADDR_STCY_REG_LSB	0x8b	//number of settling time cycle addr lsb

#define AD5933_ADDR_STAT_REG_MSB	0x8f	//status reg addr

#define AD5933_ADDR_TEMP_REG_MSB	0x92	//temperature addr msb
#define AD5933_ADDR_TEMP_REG_LSB	0x93	//temperature addr lsb

#define AD5933_ADDR_REAL_REG_MSB	0x94	//real data addr msb
#define AD5933_ADDR_REAL_REG_LSB	0x95	//real data addr lsb

#define AD5933_ADDR_IMGN_REG_MSB	0x96	//Imaginary data  addr msb
#define AD5933_ADDR_IMGN_REG_LSB	0x97	//Imaginary data  addr lsb

#endif /* AD5933_H_ */
