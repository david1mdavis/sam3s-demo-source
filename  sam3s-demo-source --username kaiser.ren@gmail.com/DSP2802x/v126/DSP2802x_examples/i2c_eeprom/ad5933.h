/*
 * ad5933.h
 *
 *  Created on: 2013-1-24
 *      Author: kren
 */

#ifndef AD5933_H_
#define AD5933_H_

/**********************************************************
 * 				Include
 **********************************************************/
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

/**********************************************************
 * 				Macro
 **********************************************************/
#define AD5933_ADDR_SLAVE	0X0D	//AD5933 I2C slave addr

#define AD5933_BOARD_SYS_CLK_SRC	(1 << 3)
#define AD5933_BOARD_SYS_CLK_FREQ	16000000ul

#define AD5933_BOARD_FREQ_START 	1000ul
#define AD5933_BOARD_FREQ_END		100000ul
#define AD5933_BOARD_FREQ_ICMT		125ul
#define AD5933_BOARD_CNT_ICMT		( (AD5933_BOARD_FREQ_END - AD5933_BOARD_FREQ_START)\
									/AD5933_BOARD_FREQ_ICMT + 1 )

#define AD5933_CMD_CODE_BLOCK_WR	0XA0	//command code, block write
#define AD5933_CMD_CODE_BLOCK_RD	0XA1	//command code, block read
#define AD5933_CMD_CODE_ADDRS_PTR	0XB1	//command code, address pointer

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

#define AD5933_STATUS_TEMP_RDY		(1 << 0)	//temperature is ready
#define AD5933_STATUS_DATA_RDY		(1 << 1)	//data is ready
#define AD5933_STATUS_SWEEP_RDY		(1 << 2)	//sweep is ready

/**********************************************************
 * 				Typedef
 **********************************************************/
typedef enum _ad5933_state_tag_{
	init_freq = 0x11,
	start_sweep = 0x21,
	icmt_freq = 0x31,
	rpet_freq = 0x41,
	meas_temp = 0x91,
	powr_down = 0xa1,
	stand_by = 0xb1
}ad5933_state_t;

#endif /* AD5933_H_ */
