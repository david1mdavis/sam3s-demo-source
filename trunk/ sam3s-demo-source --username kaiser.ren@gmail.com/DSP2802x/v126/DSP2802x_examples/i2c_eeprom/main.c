/*
 * main.c
 *
 *  Created on: 2013-1-24
 *      Author: kren
 */
/**********************************************************
 * 				Include
 **********************************************************/

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
	Uint16 value1, value2;
	unsigned char  tempString[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.I2CINT1A = &i2c_int1a_isr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2802x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   //I2CA_Init();	//use interrupt
   I2C_Init();		//use polling

// Step 5. Com port initial
   scia_echoback_init();
   scia_msg("-- Network Analyzer V0.01--\r\n");

// Step 6. BSP init, LEDs & Button
   led_init();
   button_init();
   //blink
   led_on(0x000f);
   led_off(0x000f);

// Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
   //PieCtrlRegs.PIEIER8.bit.INTx1 = 1;

// Enable CPU INT8 which is connected to PIE group 8
   //IER |= M_INT8;
   //EINT;

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
	   while( 1 == GpioDataRegs.GPADAT.bit.GPIO12){
		   //start freq sweep
		   ad5933_mode(start_sweep);

		   //check whether sweep is completed?
		   while( 0 == ( AD5933_STATUS_SWEEP_RDY & ad5993_status() ) ){
			   //wait for data valid
			   while( 0 == ( AD5933_STATUS_DATA_RDY & ad5993_status() ) );

			   //read real data
			   value1 = I2C_Read(AD5933_ADDR_REAL_REG_MSB);
			   value2 = I2C_Read(AD5933_ADDR_REAL_REG_LSB);
			   scia_msg("Real: ");
			   scia_xmit(value1);
			   scia_xmit(value2);
			   scia_msg("\r\n");

			   //read imaginary data
			   value1 = I2C_Read(AD5933_ADDR_IMGN_REG_MSB);
			   value2 = I2C_Read(AD5933_ADDR_IMGN_REG_LSB);
			   scia_msg("Imaginary: ");
			   scia_xmit(value1);
			   scia_xmit(value2);
			   scia_msg("\r\n");

			   //go to next freq point
			   ad5933_mode(icmt_freq);
		   }

		   //sweep complete, goto power-down mode
		   ad5933_mode(powr_down);
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
