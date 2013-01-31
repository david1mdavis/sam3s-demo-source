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

//void pass(void);
//void fail(void);



// Global variables
// Two bytes will be used for the outgoing address,
// thus only setup 14 bytes maximum


void main(void)
{
   Uint16 Error;
   Uint16 i;

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

   // Clear incoming message buffer
   for (i = 0; i < (I2C_MAX_BUFFER_SIZE - 2); i++)
   {
       I2cMsgIn1.MsgBuffer[i] = i;
   }

// Enable interrupts required for this example

// Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
   PieCtrlRegs.PIEIER8.bit.INTx1 = 1;

// Enable CPU INT8 which is connected to PIE group 8
   IER |= M_INT8;
   EINT;

   // Application loop
   for(;;)
   {
      //////////////////////////////////
      // Write data to EEPROM section //
      //////////////////////////////////

      // Check the outgoing message to see if it should be sent.
      // In this example it is initialized to send with a stop bit.
      if(I2cMsgOut1.MsgStatus == I2C_MSGSTAT_SEND_WITHSTOP)
      {
         Error = I2CA_WriteData(&I2cMsgOut1);
         // If communication is correctly initiated, set msg status to busy
         // and update CurrentMsgPtr for the interrupt service routine.
         // Otherwise, do nothing and try again next loop. Once message is
         // initiated, the I2C interrupts will handle the rest. Search for
         // ICINTR1A_ISR in the i2c_eeprom_isr.c file.
         if (Error == I2C_SUCCESS)
         {
            CurrentMsgPtr = &I2cMsgOut1;
            I2cMsgOut1.MsgStatus = I2C_MSGSTAT_WRITE_BUSY;
         }
      }  // end of write section

      ///////////////////////////////////
      // Read data from EEPROM section //
      ///////////////////////////////////

      // Check outgoing message status. Bypass read section if status is
      // not inactive.
      if (I2cMsgOut1.MsgStatus == I2C_MSGSTAT_INACTIVE)
      {
         // Check incoming message status.
         if(I2cMsgIn1.MsgStatus == I2C_MSGSTAT_SEND_NOSTOP)
         {
            // EEPROM address setup portion
            while(I2CA_ReadData(&I2cMsgIn1) != I2C_SUCCESS)
            {
               // Maybe setup an attempt counter to break an infinite while
               // loop. The EEPROM will send back a NACK while it is performing
               // a write operation. Even though the write communique is
               // complete at this point, the EEPROM could still be busy
               // programming the data. Therefore, multiple attempts are
               // necessary.
            }
            // Update current message pointer and message status
            CurrentMsgPtr = &I2cMsgIn1;
            I2cMsgIn1.MsgStatus = I2C_MSGSTAT_SEND_NOSTOP_BUSY;
         }

         // Once message has progressed past setting up the internal address
         // of the EEPROM, send a restart to read the data bytes from the
         // EEPROM. Complete the communique with a stop bit. MsgStatus is
         // updated in the interrupt service routine.
         else if(I2cMsgIn1.MsgStatus == I2C_MSGSTAT_RESTART)
         {
            // Read data portion
            while(I2CA_ReadData(&I2cMsgIn1) != I2C_SUCCESS)
            {
               // Maybe setup an attempt counter to break an infinite while
               // loop.
            }
            // Update current message pointer and message status
            CurrentMsgPtr = &I2cMsgIn1;
            I2cMsgIn1.MsgStatus = I2C_MSGSTAT_READ_BUSY;
         }
      }  // end of read section

   }   // end of for(;;)
}   // end of main




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
