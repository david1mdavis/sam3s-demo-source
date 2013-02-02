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
// Note: I2C Macros used in this example can be found in the
// DSP2802x_I2C_defines.h file


// Prototype statements for functions found within this file.
void led_init(void);
void led_on(Uint16 led_msk);
void led_off(Uint16 led_msk);
void button_init(void);
//void pass(void);
//void fail(void);



// Global variables
// Two bytes will be used for the outgoing address,
// thus only setup 14 bytes maximum


void main(void)
{
   CurrentMsgPtr = &I2cMsgOut1;

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
   I2CA_Init();

// Step 5. User specific code

   // Clear Counters
   PassCount = 0;
   FailCount = 0;

// Step 6. LEDs and Button init
   led_init();
   button_init();

   led_on(0x000f);
   led_off(0x000f);
   led_on(0x000f);
   led_off(0x000f);
   led_on(0x000f);

// Enable interrupts required for this example

// Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
   PieCtrlRegs.PIEIER8.bit.INTx1 = 1;

// Enable CPU INT8 which is connected to PIE group 8
   IER |= M_INT8;
   EINT;

// Step 7. Initial AD5933
   ad5933_init();

   // Application loop
   for(;;)
   {
	   while( 1 == GpioDataRegs.GPADAT.bit.GPIO12){
		   //start freq sweep
		   ad5933_mode(start_sweep);

		   //check whether sweep is completed?
		   while( 0 == ( AD5933_STATUS_SWEEP_RDY & ad5993_status() ) ){
			   //wait for data valid
			   while( 0 == ( AD5933_STATUS_DATA_RDY & ad5993_status() ) );

			   //read real and imaginary data

			   //go to next freq point
			   ad5933_mode(icmt_freq);
		   }

		   //sweep complete, goto power-down mode
		   ad5933_mode(powr_down);
	   }

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

/*
void pass()
{
    asm("   ESTOP0");
    for(;;);
}

void fail()
{
    asm("   ESTOP0");
    for(;;);
}
*/
//===========================================================================
// No more.
//===========================================================================
