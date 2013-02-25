/*
 * ad5933.c
 *
 *  Created on: 2012-11-26
 *      Author: cui
 */
/**********************************************************
 * 				Include
 **********************************************************/
#include <math.h>
#include "ad5933.h"
#include "Communication.h"
#include "Example_2802xI2C_eeprom/com.h"
#include "IQmathLib.h"

/**********************************************************
 * 				Macro
 **********************************************************/

/**********************************************************
 * 				Global Variable
 **********************************************************/
//ad5933_data_field_t data_part[AD5933_BOARD_CNT_ICMT];
double magnitude[AD5933_BOARD_CNT_ICMT];
Uint16 ad5933_temp = 0;
/**********************************************************
 * 				Prototype
 **********************************************************/

/**********************************************************
 * 				function
 **********************************************************/
/**
 * ad5933 initialization
 */
void ad5933_init(void)
{
	Uint32 start_freq;
	Uint32 incre_freq;
	Uint16 incre_num;
	Uint16 cycle_set;

	start_freq = AD5933_BOARD_FREQ_END - AD5933_BOARD_FREQ_ICMT*AD5933_BOARD_CNT_ICMT;
	start_freq = start_freq * ( 4 * AD5933_BOARD_CALC_FACTOR / AD5933_BOARD_SYS_CLK_FREQ);
	start_freq = start_freq/1000;
	incre_freq = AD5933_BOARD_FREQ_ICMT * ( 4 * AD5933_BOARD_CALC_FACTOR / AD5933_BOARD_SYS_CLK_FREQ);
	incre_freq = incre_freq/1000;
	incre_num = AD5933_BOARD_CNT_ICMT;
	cycle_set = 511;

	//set start frequency
	I2C_Write(AD5933_ADDR_FREQ_REG_MSB, start_freq >> 16);	//REG 0x82
	I2C_Write(AD5933_ADDR_FREQ_REG_MMB, start_freq >> 8);	//REG 0x83
	I2C_Write(AD5933_ADDR_FREQ_REG_LSB, start_freq >> 0);	//REG 0x84

	//set frequency increment
	I2C_Write(AD5933_ADDR_FICT_REG_MSB, incre_freq >> 16);	//REG 0x85
	I2C_Write(AD5933_ADDR_FICT_REG_MMB, incre_freq >> 8);	//REG 0x86
	I2C_Write(AD5933_ADDR_FICT_REG_LSB, incre_freq >> 0);	//REG 0x87

	//set number of increment, this reg allow maximum value, 0x1FF
	I2C_Write(AD5933_ADDR_NICT_REG_MSB, incre_num >> 8);	//REG 0x88
	I2C_Write(AD5933_ADDR_NICT_REG_LSB, incre_num >> 0);	//REG 0x89

	//set number of setting time cycle
	I2C_Write(AD5933_ADDR_STCY_REG_MSB, cycle_set >> 8);	//REG 0x8a
	I2C_Write(AD5933_ADDR_STCY_REG_LSB, cycle_set >> 0);	//REG 0x8b

	//set clock source selection to access CTRL LSB, EXT_CLK
	//I2C_Write(AD5933_ADDR_CTRL_REG_LSB, AD5933_REG_CTRL_CLK);	//REG 0x81
}

/**
 * ad5933 test
 */
void ad5933_print(void)
{
	unsigned char i, revByte;

	for(i = 0x80; i < 0x8c; i++)
	{
		revByte = I2C_Read( i );
		scia_Byte2Hex( revByte );
		scia_PrintLF();
	}
}

/*
 * ad5933 mode switch
 */
void ad5933_mode(ad5933_state_t state)
{
	//WR in reg 0x80
	I2C_Write(AD5933_ADDR_CTRL_REG_MSB, (unsigned char)state);	//REG 0x80
}

/*
 * ad5933 status read.
 */
unsigned char ad5993_status(void)
{
	unsigned char c;

	//read status
	c = I2C_Read(AD5933_ADDR_STAT_REG_MSB);
	return ( c );
}

/*
 * ad5933 sweep
 */
void ad5933_sweep(void)
{
	Uint16 temp, cnt;
	int16  real, imaginary;
	unsigned char value1, value2, status;

	//start freq sweep
	ad5933_mode(stand_by);
	ad5933_mode(init_freq);
	ad5933_mode(start_sweep);
	DELAY_US(100000);    // Delay 100ms , wait
	//check whether sweep is completed?
	status = 0;
	cnt = 0;
	while( 1 )
	{
		while( 0 == (status & AD5933_STATUS_DATA_RDY) )
		{
			status = ad5993_status();
		}
		//blink for start indicator
		led_on(0x000f);

		scia_msg("I:");
	    scia_Byte2Hex(cnt);
		//read real data
		value1 = I2C_Read(AD5933_ADDR_REAL_REG_MSB);
		value2 = I2C_Read(AD5933_ADDR_REAL_REG_LSB);
		temp = ( (Uint16)value1 ) << 8 | value2;
		scia_msg("R:");
		scia_Byte2Hex(temp);
		real = temp;

		//read imaginary data
		value1 = I2C_Read(AD5933_ADDR_IMGN_REG_MSB);
		value2 = I2C_Read(AD5933_ADDR_IMGN_REG_LSB);
		temp = ( (Uint16)value1 ) << 8 | value2;
		scia_msg("I:");
		scia_Byte2Hex(temp);
		scia_PrintLF();
		imaginary = temp;

		magnitude[cnt] = _IQmag(real , imaginary);
		led_off(0x000f);

		cnt++;
		status = ad5993_status();
		if( AD5933_STATUS_SWEEP_RDY & status ){
			break;
		}
		else
		{
			//go to next freq point
			ad5933_mode(icmt_freq);
		}
	}

	//sweep complete, goto power-down mode
	scia_PrintLF();
	ad5933_mode(powr_down);
}

/***************************************************************************//**
 * @brief Reads the temperature from the part and returns the data in
 *        degrees Celsius.
 *
 * @return temperature - Temperature.
*******************************************************************************/
char ad5993_GetTemperature(void)
{
    Uint16 temp= 0;
    unsigned char status = 0;

    ad5933_mode(meas_temp);

    while((status & AD5933_STATUS_TEMP_RDY) == 0)
    {
        status = ad5993_status();
    }

    temp = I2C_Read(AD5933_ADDR_TEMP_REG_MSB);
    temp = temp << 8;
    temp |= I2C_Read(AD5933_ADDR_TEMP_REG_LSB);
    if(temp < 8192)
    {
    	temp = temp >> 5;
    }
    else
    {
    	temp -= 16384;
    	temp /= 32;
    }
    ad5933_temp = temp;
    return((char)temp);
}

//eof
