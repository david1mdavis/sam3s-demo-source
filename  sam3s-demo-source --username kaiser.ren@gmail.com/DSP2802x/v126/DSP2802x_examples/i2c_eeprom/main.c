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
#include "calc.h"
#include "Communication.h"
#include "Example_2802xI2C_eeprom/com.h"
#include "IQmathLib.h"
#include "IQlog.h"
#include <stdio.h>
// Note: I2C Macros used in this example can be found in the
// DSP2802x_I2C_defines.h file


// Prototype statements for functions found within this file.
void led_init(void);
void led_on(Uint16 led_msk);
void led_off(Uint16 led_msk);
void button_init(void);
void GPIOx_Init(void);
void GPIOx_Set(Uint16 pin );
void GPIOx_Clear(Uint16 pin );

// Global variables
const unsigned char ledArray[7] = {4, 5, 6, 7, 16, 17, 18};
const unsigned char encoderArray[4] = {0, 1, 2, 3};


void main(void)
{
	char s1[32];
	unsigned char flag = 0;

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
#ifndef _DEBUG
   // Copy time critical code and Flash setup code to RAM
   // This includes the following ISR functions: EPwm1_timer_isr(), EPwm2_timer_isr()
   // EPwm3_timer_isr and and InitFlash();
   // The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
   // symbols are created by the linker. Refer to the F2808.cmd file.
      MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

   // Call Flash Initialization to setup flash waitstates
   // This function must reside in RAM
      InitFlash();
#endif
// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2802x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   I2C_Init();		//use polling

// Step 5. Com port initial
   scia_echoback_init();
   scia_msg("-- Network Analyzer V0.03--\r\n");
   scia_msg("-- Build On: "__DATE__" "__TIME__"--\r\n");
   scia_msg("-- Start: 36.125KHz--\r\n");
   scia_msg("-- End:   100kHz   --\r\n");
   scia_msg("-- Step : 125Hz    --\r\n");
   scia_msg("-- Point: 511      --\r\n");

// Step 6. BSP init, LEDs & Button
   led_init();
   button_init();
   GPIOx_Init();
   //blink
   led_on(0x007f);
   led_off(0x007f);
   //clear GPIO0~GPIO3
   GPIOx_Clear(0x000f);

// Step 7. Initial AD5933
   ad5933_init();

   // Application loop
   for(;;)
   {
	   /*
	    * GPIO12 pressed routine
	    */
	   while( (0 == GpioDataRegs.GPADAT.bit.GPIO12)
			   && ( 0 == GpioDataRegs.GPADAT.bit.GPIO19 ) ){};
	   //GPIO12 pressed
	   if(1 == GpioDataRegs.GPADAT.bit.GPIO12)
	   {
		  //clear GPIO0~GPIO3
		  GPIOx_Clear(0x000f);
		  DELAY_US(100000);    // Delay 100ms , wait
		  sprintf(s1,"Temperature=%d\r\n", ad5993_GetTemperature());
		  scia_msg(s1);
		  ad5933_sweep( 0x0001 << 0, mag_ref);
		  //led indicator
		  led_off(0x007f);
		  if( diff_variance < AD5933_STANDARD_VARIANCE )
		  {
			  led_off(0x01 << 0);	//led0 off
			  led_off(0x01 << 6);	//led6 off
			  sprintf(s1,"Ref larger than standard.\r\n" );
			  scia_msg(s1);
		  }
		  else
		  {
			  led_on(0x01 << 0);	//led0 on
			  led_on(0x01 << 6);	//led6 on
			  sprintf(s1,"Ref less than standard.\r\n" );
			  scia_msg(s1);
		  }
		  scia_PrintLF();
	   }

	   /*
	    * GPIO19 pressed routine
	    */
	   if( 1 == GpioDataRegs.GPADAT.bit.GPIO19)
	   {
		   //clear flag
		   flag = 0;

		   //GROUP1--0b1010
		   //clear GPIO0~GPIO3
		   GPIOx_Clear(0x000f);
		   //set GPIO1 GPIO3
		   GPIOx_Set(0x000A);
		   // Delay 100ms , wait
		   DELAY_US(100000);
		   sprintf(s1,"Temperature=%d\r\n", ad5993_GetTemperature());
		   scia_msg(s1);
		   ad5933_sweep(0x0001 << 0, mag_ref0);;
		   //led0 indicator
		   led_off(0x007f);
		   if( diff_variance < AD5933_STANDARD_VARIANCE )
		   {
		   	  led_off(0x01 << 0);	//led0 off
			  sprintf(s1,"Group0 Ref larger than standard.\r\n" );
			  scia_msg(s1);
		   }
		   else
		   {
		   	  led_on(0x01 << 0);	//led0 on
		   	  flag++;
              sprintf(s1,"Group0 Ref less than standard.\r\n" );
			  scia_msg(s1);
		   }
		   scia_PrintLF();

		   //GROUP2--0b0101
		   //clear GPIO0~GPIO3
		   GPIOx_Clear(0x000f);
		   //set GPIO0 GPIO2
		   GPIOx_Set(0x0005);
		   // Delay 100ms , wait
		   DELAY_US(100000);
		   sprintf(s1,"Temperature=%d\r\n", ad5993_GetTemperature());
		   scia_msg(s1);
		   ad5933_sweep(0x0001 << 1, mag_ref1);
		   //led1 indicator
		   led_off(0x007f);
		   if( diff_variance < AD5933_STANDARD_VARIANCE )
		   {
		   	  led_off(0x01 << 1);	//led1 off
			  sprintf(s1,"Group1 Ref larger than standard.\r\n" );
			  scia_msg(s1);
		   }
		   else
		   {
		   	  led_on(0x01 << 1);	//led1 on
		   	  flag++;
			  sprintf(s1,"Group1 Ref less than standard.\r\n" );
			  scia_msg(s1);
		   }
		   scia_PrintLF();

		   //GROUP3--0b1111
		   //clear GPIO0~GPIO3
		   GPIOx_Clear(0x000f);
		   //set GPIO0~GPIO3
		   GPIOx_Set(0x000F);
		   // Delay 100ms , wait
		   DELAY_US(100000);
		   sprintf(s1,"Temperature=%d\r\n", ad5993_GetTemperature());
		   scia_msg(s1);
		   ad5933_sweep(0x0001 << 2, mag_ref2);
		   //led2 indicator
		   led_off(0x007f);
		   if( diff_variance < AD5933_STANDARD_VARIANCE )
		   {
		   	  led_off(0x01 << 2);	//led2 off
              sprintf(s1,"Group2 Ref larger than standard.\r\n" );
			  scia_msg(s1);
		   }
		   else
		   {
		   	  led_on(0x01 << 2);	//led2 on
		   	  flag++;
			  sprintf(s1,"Group2 Ref less than standard.\r\n" );
			  scia_msg(s1);
		   }
		   scia_PrintLF();

		   //GROUP4--0b1110
		   //clear GPIO0~GPIO3
		   GPIOx_Clear(0x000f);
		   //set GPIO1~GPIO3
		   GPIOx_Set(0x000E);
		   // Delay 100ms , wait
		   DELAY_US(100000);
		   sprintf(s1,"Temperature=%d\r\n", ad5993_GetTemperature());
		   scia_msg(s1);
		   ad5933_sweep(0x0001 << 3, mag_ref3);
		   //led3 indicator
		   led_off(0x007f);
		   if( diff_variance < AD5933_STANDARD_VARIANCE )
		   {
		   	  led_off(0x01 << 3);	//led3 off
  			  sprintf(s1,"Group3 Ref larger than standard.\r\n" );
			  scia_msg(s1);
		   }
		   else
		   {
		   	  led_on(0x01 << 3);	//led3 on
		   	  flag++;
			  sprintf(s1,"Group3 Ref less than standard.\r\n" );
			  scia_msg(s1);
		   }
		   scia_PrintLF();

		   //GROUP5--0b0110
		   //clear GPIO0~GPIO3
		   GPIOx_Clear(0x000f);
		   //set GPIO2~GPIO3
		   GPIOx_Set(0x0006);
		   // Delay 100ms , wait
		   DELAY_US(100000);
		   sprintf(s1,"Temperature=%d\r\n", ad5993_GetTemperature());
		   scia_msg(s1);
		   ad5933_sweep(0x0001 << 4, mag_ref4);
		   //led4 indicator
		   led_off(0x007f);
		   if( diff_variance < AD5933_STANDARD_VARIANCE )
		   {
		   	  led_off(0x01 << 4);	//led4 off
			  sprintf(s1,"Group4 Ref larger than standard.\r\n" );
			  scia_msg(s1);
		   }
		   else
		   {
		   	  led_on(0x01 << 4);	//led4 on
		   	  flag++;
			  sprintf(s1,"Group4 Ref less than standard.\r\n" );
			  scia_msg(s1);
		   }
		   scia_PrintLF();

		   //GROUP6--0b1101
		   //clear GPIO0~GPIO3
		   GPIOx_Clear(0x000f);
		   //set GPIO0 GPIO2 GPIO3
		   GPIOx_Set(0x000D);
		   // Delay 100ms , wait
		   DELAY_US(100000);
		   sprintf(s1,"Temperature=%d\r\n", ad5993_GetTemperature());
		   scia_msg(s1);
		   ad5933_sweep(0x0001 << 5, mag_ref5);
		   //led5 indicator
		   led_off(0x007f);
		   if( diff_variance < AD5933_STANDARD_VARIANCE )
		   {
		   	  led_off(0x01 << 5);	//led5 off
			  sprintf(s1,"Group5 Ref larger than standard.\r\n" );
			  scia_msg(s1);
		   }
		   else
		   {
		   	  led_on(0x01 << 5);	//led5 on
		   	  flag++;
			  sprintf(s1,"Group5 Ref less than standard.\r\n" );
			  scia_msg(s1);
		   }
		   scia_PrintLF();

		   if(6 == flag)
		   {
			   led_on(0x01 << 6);	//led6 on
 			   sprintf(s1,"total less than standard.\r\n" );
			   scia_msg(s1);
		   }
		   else
		   {
			   led_off(0x01 << 6);	//led6 off
			   sprintf(s1,"any larger than standard.\r\n" );
			   scia_msg(s1);
		   }

		   //the end
		   //clear GPIO0~GPIO3
		   GPIOx_Clear(0x000f);
	   }

   }   // end of for(;;)
}   // end of main


void led_init(void)
{
	EALLOW;
	// GPIO4, 5, 6, 7, 16, 17, 18 as general purpose
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;


	//output direction
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;


	//clear corresponding pin
	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;
	EDIS;
}
void led_on(Uint16 led_msk)
{
	if( led_msk & (0x0001 << 0) )
	{
		GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
	}

	if( led_msk & (0x0001 << 1) )
	{
		GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
	}

	if( led_msk & (0x0001 << 2) )
	{
		GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
	}

	if( led_msk & (0x0001 << 3) )
	{
		GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
	}

	if( led_msk & (0x0001 << 4) )
	{
		GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;
	}

	if( led_msk & (0x0001 << 5) )
	{
		GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;
	}

	if( led_msk & (0x0001 << 6) )
	{
		GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;
	}
}

void led_off(Uint16 led_msk)
{
	if( led_msk & (0x0001 << 0) )
	{
		GpioDataRegs.GPASET.bit.GPIO4 = 1;
	}

	if( led_msk & (0x0001 << 1) )
	{
		GpioDataRegs.GPASET.bit.GPIO5 = 1;
	}

	if( led_msk & (0x0001 << 2) )
	{
		GpioDataRegs.GPASET.bit.GPIO6 = 1;
	}

	if( led_msk & (0x0001 << 3) )
	{
		GpioDataRegs.GPASET.bit.GPIO7 = 1;
	}

	if( led_msk & (0x0001 << 4) )
	{
		GpioDataRegs.GPASET.bit.GPIO16 = 1;
	}

	if( led_msk & (0x0001 << 5) )
	{
		GpioDataRegs.GPASET.bit.GPIO17 = 1;
	}

	if( led_msk & (0x0001 << 6) )
	{
		GpioDataRegs.GPASET.bit.GPIO18 = 1;
	}
}

/*
 * GPIOx initial.
 */
void GPIOx_Init(void)
{
	EALLOW;
	// GPIO0, 1, 2, 3, 4 as general purpose
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;

	// GPIO0, 1, 2, 3, 4 as output dir
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;

	GpioDataRegs.GPACLEAR.all = 0x000F;
	EDIS;
}

/*
 * GPIOx Set.
 */
void GPIOx_Set(Uint16 pin_msk )
{
	unsigned char i;

	for(i = 0; i < 4; i++)
	{
		if( pin_msk & (0x0001 << i) )
		{
			GpioDataRegs.GPASET.all = 1 << encoderArray[i];
		}
	}
}

/*
 * GPIOx Clear.
 */
void GPIOx_Clear(Uint16 pin_msk )
{
	unsigned char i;

	for(i = 0; i < 4; i++)
	{
		if( pin_msk & (0x0001 << i) )
		{
			GpioDataRegs.GPACLEAR.all = 1 << encoderArray[i];
		}
	}
}
void button_init(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;	// gpio12 as general purpose
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;    	// gpio12 input dir
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;		// gpio12 pull-up enable

	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;	// gpio19 as general purpose
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;    	// gpio19 input dir
	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;		// gpio19 pull-up enable
	EDIS;
}

//===========================================================================
// No more.
//===========================================================================
