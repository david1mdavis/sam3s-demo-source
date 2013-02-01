// TI File $Revision: /main/2 $
// Checkin $Date: October 16, 2009   15:43:28 $
//###########################################################################
//
// FILE:    Example_2802xI2c_eeprom.c
//
// TITLE:   DSP2802x I2C EEPROM Example
//
// ASSUMPTIONS:
//
//    This program requires the DSP2802x header files.
//
//    This program requires an external I2C EEPROM connected to
//    the I2C bus at address 0x50.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//    $Boot_Table
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:   EMU_KEY        EMU_BMODE
//                   (0xD00)         (0xD01)
//      ---------------------------------------
//      Wait         !=0x55AA        X
//      I/O          0x55AA          0x0000
//      SCI          0x55AA          0x0001
//      Wait         0x55AA          0x0002
//      Get_Mode     0x55AA          0x0003
//      SPI          0x55AA          0x0004
//      I2C          0x55AA          0x0005
//      OTP          0x55AA          0x0006
//      Wait         0x55AA          0x0007
//      Wait         0x55AA          0x0008
//      SARAM        0x55AA          0x000A   <-- "Boot to SARAM"
//      Flash        0x55AA          0x000B
//      Wait         0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
// DESCRIPTION:
//
//    This program will write 1-14 words to EEPROM and read them back.
//    The data written and the EEPROM address written to are contained
//    in the message structure, I2cMsgOut1. The data read back will be
//    contained in the message structure I2cMsgIn1.
//
//    This program will work with the on-board I2C EEPROM supplied on
//    the F2802x eZdsp.
//
//
//###########################################################################
// Original Author: D.F.
//
// $TI Release: 2802x C/C++ Header Files V1.26 $
// $Release Date: February 2, 2010 $
//###########################################################################

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

// Step 7. Initial AD5933
   I2CA_Init();
   ad5933_init();

// Enable interrupts required for this example

// Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
   PieCtrlRegs.PIEIER8.bit.INTx1 = 1;

// Enable CPU INT8 which is connected to PIE group 8
   IER |= M_INT8;
   EINT;

   // Application loop
   for(;;)
   {
	   while( 1 == GpioDataRegs.GPADAT.bit.GPIO12){
		   led_on(0x0000);
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
