/*
 * main.c
 *
 *  Created on: 2012-11-26
 *      Author: cui
 */
/**********************************************************
 * 				Include
 **********************************************************/
#include <stdlib.h>
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "ad5933.h"
#include "Communication.h"
#include "Example_2802xI2C_eeprom/com.h"
// Note: I2C Macros used in this example can be found in the
// DSP2802x_I2C_defines.h file


// Prototype statements for functions found within this file.
void led_init(void);
void led_on(Uint16 led_msk);
void led_off(Uint16 led_msk);
void button_init(void);

// Global variables
// Two bytes will be used for the outgoing address,
// thus only setup 14 bytes maximum


void main(void)
{
	unsigned char revByte;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2802x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2802x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();
// Setup only the GP I/O only for I2C functionality
   InitI2CGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2802x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2802x_DefaultIsr.c.
// This function is found in DSP2802x_PieVect.c.
   InitPieVectTable();

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2802x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   I2C_Init();		//use polling

// Step 5. Com port initial
   scia_echoback_init();
   scia_msg("-- Network Analyzer V0.02--\r\n");
   scia_msg("-- Build On: "__DATE__" "__TIME__"--\r\n");
   scia_msg("-- Start: 36.125KHz--\r\n");
   scia_msg("-- End:   100kHz   --\r\n");
   scia_msg("-- Step : 125Hz    --\r\n");
   scia_msg("-- Point: 511      --\r\n");
// Step 6. BSP init, LEDs & Button
   led_init();
   button_init();
   //blink
   led_on(0x000f);
   led_off(0x000f);

// Step 7. Initial AD5933
   ad5933_init();

   // Application loop
   for(;;)
   {
#if 0	//comment out AD7414
	   I2C_Write(0x01, 0x40);	//AD7414 ctrl reg
	   I2C_Write(0x02, 0xa5);	//AD7414 t-high reg
	   I2C_Write(0x03, 0x5a);	//AD7414 t-low reg
	   DELAY_US(50);    		//Delay 50us ,wait
	   value1 = I2C_Read(0x00);	//read ctrl reg
	   FloatToString(tempString, (double) value1);
	   scia_msg(tempString);
	   value1 = 0;
	   value1 = I2C_Read(0x01);	//read ctrl reg
	   value1 = 0;
	   value1 = I2C_Read(0x02);	//read t-high reg
	   value1 = 0;
	   value1 = I2C_Read(0x03);	//read t-low reg
	   value1 = 0;
#else
	   revByte = scia_read();
	   switch(revByte)
	   {
	   	   case 't':
	   	   case 'T':
	   		   scia_msg("Input 't' \r\ntemperature: ");
	   		   scia_Byte2Hex( ad5993_GetTemperature() );
	   		   scia_PrintLF();
	   		   scia_PrintLF();
	   		   scia_PrintLF();
	   		   break;
	   		   //
	   	   case 's':
	   	   case 'S':
	   		   scia_msg("Input 's'\r\n");
	   		   ad5933_sweep();
	   		   scia_PrintLF();
	   		   scia_PrintLF();
	   		   break;
	   		   //
	   	   case 'r':
	   	   case 'R':
	   		   scia_msg("Input 'r' \r\nreg 80~8B\r\n");
	   		   ad5933_print();
	   		   scia_PrintLF();
	   		   scia_PrintLF();
	   		   break;
	   		   //
	   	   case 'h':
	   	   case 'H':
	   		   scia_msg("-- help menu --\r\n");
	   		   scia_msg("h: print help menu\r\n");
	   		   scia_msg("t: print temperature\r\n");
	   		   scia_msg("s: start ad5933 sweep\r\n");
	   		   scia_msg("r: read ad5933 register\r\n");
	   		   scia_PrintLF();
	   		   scia_PrintLF();
	   		   break;
	   		   //
	   	   default:
	   		   break;
	   		   //
	   }
#endif
   }   // end of for(;;)
}   // end of main


void led_init(void)
{
	EALLOW;
	// gpio0, 1, 2, 3 as general purpose
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;

	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;    //gpio0 output dir
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;    //gpio1 output dir
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;    //gpio2 output dir
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;    //gpio3 output dir
	EDIS;
}
void led_on(Uint16 led_msk)
{
	//led0
	if(led_msk & ( 0x0001 << 0) ){
		GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
	}

	//led1
	if(led_msk & ( 0x0001 << 1) ){
		GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
	}

	//led2
	if(led_msk & ( 0x0001 << 2) ){
		GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
	}

	//led3
	if(led_msk & ( 0x0001 << 3) ){
		GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
	}
}

void led_off(Uint16 led_msk)
{
	//led0
	if(led_msk & ( 0x0001 << 0) ){
		GpioDataRegs.GPASET.bit.GPIO0 = 1;
	}

	//led1
	if(led_msk & ( 0x0001 << 1) ){
		GpioDataRegs.GPASET.bit.GPIO1 = 1;
	}

	//led2
	if(led_msk & ( 0x0001 << 2) ){
		GpioDataRegs.GPASET.bit.GPIO2 = 1;
	}

	//led3
	if(led_msk & ( 0x0001 << 3) ){
		GpioDataRegs.GPASET.bit.GPIO3 = 1;
	}
}
void button_init(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;	// gpio12 as general purpose
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;    	// gpio12 input dir
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;		// gpio12 pull-up enable
	EDIS;
}

//===========================================================================
// No more.
//===========================================================================
