/*
 * ad5933.h
 *
 *  Created on: 2012-11-26
 *      Author: cui
 */

#ifndef AD5933_H_
#define AD5933_H_

/**********************************************************
 * 				Include
 **********************************************************/
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
//#include "DSP2802x_Device.h"     // Headerfile Include File
/**********************************************************
 * 				Macro
 **********************************************************/
#define AD5933_ADDR_SLAVE	0x0D	//AD5933 I2C slave addr

#define AD5933_ADDR_SLAVE_WR	0x00	//write bit following addr
#define AD5933_ADDR_SLAVE_RD	0x01	//read bit following addr

#define AD5933_REG_CTRL_CLK	(0x01 << 3)	//ext clock
#define AD5933_REG_CTRL_RST	(0x01 << 4)
#define AD5933_BOARD_SYS_CLK_FREQ	16000ul

#define AD5933_BOARD_CALC_FACTOR	0x8000000ul

#define AD5933_BOARD_CMD_BLOCK_WR	0xa0
#define AD5933_BOARD_CMD_BLOCK_RD 	0xa1
#define AD5933_BOARD_CMD_ADDR_PTR	0xb0

#define AD5933_BOARD_FREQ_START 	45000ul
#define AD5933_BOARD_FREQ_END		100000ul
#define AD5933_BOARD_FREQ_ICMT		125ul
#define AD5933_BOARD_CNT_ICMT		511ul	//maximum

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

#define AD5933_STATUS_TEMP_RDY		(0x01 << 0)	//temperature is ready
#define AD5933_STATUS_DATA_RDY		(0x01 << 1)	//data is ready
#define AD5933_STATUS_SWEEP_RDY		(0x01 << 2)	//sweep is ready

/**********************************************************
 * 				Typedef
 **********************************************************/
//PGA gain = x1
typedef enum _ad5933_state_tag_{
	init_freq = 0x11,
	start_sweep = 0x21,
	icmt_freq = 0x31,
	rpet_freq = 0x41,
	meas_temp = 0x91,
	powr_down = 0xa1,
	stand_by = 0xb1
}ad5933_state_t;

typedef struct _ad5933_data_field_tag_
{
	int16 real;
	int16 imaginary;
	//float magnitude;
}ad5933_data_field_t;

/**********************************************************
 * 				Extern
 **********************************************************/
extern struct I2CMSG I2cMsgOut1;
extern struct I2CMSG I2cMsgIn1;
extern struct I2CMSG *CurrentMsgPtr;
extern Uint16 PassCount;
extern Uint16 FailCount;

/**********************************************************
 * 				Prototype
 **********************************************************/
void   I2CA_Init(void);
Uint16 I2CA_WriteData(struct I2CMSG *msg);
Uint16 I2CA_ReadData(struct I2CMSG *msg);
interrupt void i2c_int1a_isr(void);
void ad5933_init(void);
void ad5933_print(void);
void ad5933_mode(ad5933_state_t state);
unsigned char ad5993_status(void);
char ad5993_GetTemperature(void);
void ad5933_sweep(void);

void led_on(Uint16 led_msk);
void led_off(Uint16 led_msk);
#endif /* AD5933_H_ */
