/*
 * ad5933.c
 *
 *  Created on: 2013-1-24
 *      Author: kren
 */
/**********************************************************
 * 				Include
 **********************************************************/
#include "ad5933.h"

/**********************************************************
 * 				Macro
 **********************************************************/
#define I2C_SLAVE_ADDR        0x0d
#define I2C_NUMBYTES          2
#define I2C_EEPROM_HIGH_ADDR  0x00
#define I2C_EEPROM_LOW_ADDR   0x30
/**********************************************************
 * 				Global Variable
 **********************************************************/
struct I2CMSG I2cMsgOut1={I2C_MSGSTAT_SEND_WITHSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          0,
                          0,
                          0x12,                   // Msg Byte 1
                          0x34};                  // Msg Byte 2


struct I2CMSG I2cMsgIn1={ I2C_MSGSTAT_SEND_NOSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          I2C_EEPROM_HIGH_ADDR,
                          I2C_EEPROM_LOW_ADDR};

struct I2CMSG *CurrentMsgPtr;               // Used in interrupts
Uint16 PassCount;
Uint16 FailCount;
/**********************************************************
 * 				Prototype
 **********************************************************/
void   I2CA_Init(void);
Uint16 I2CA_WriteData(struct I2CMSG *msg);
Uint16 I2CA_ReadData(struct I2CMSG *msg);
interrupt void i2c_int1a_isr(void);
void ad5933_init(void);
void ad5933_mode(ad5933_state_t state);
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

	start_freq = AD5933_BOARD_FREQ_START * ( 4 * AD5933_BOARD_CALC_FACTOR / AD5933_BOARD_SYS_CLK_FREQ);
	start_freq = start_freq/1000;
	incre_freq = AD5933_BOARD_FREQ_ICMT * ( 4 * AD5933_BOARD_CALC_FACTOR / AD5933_BOARD_SYS_CLK_FREQ);
	incre_freq = incre_freq/1000;
	incre_num = AD5933_BOARD_CNT_ICMT;
	cycle_set = 511;

	//set address pointer, to 0x82,
	/*I2cMsgOut1.NumOfBytes = 2;	//POINTER CMD and REG Addr
	I2cMsgOut1.MsgBuffer[0] = AD5933_BOARD_CMD_ADDR_PTR;
	I2cMsgOut1.MsgBuffer[1] = AD5933_ADDR_FREQ_REG_MSB;
	I2CA_WriteData(&I2cMsgOut1);*/

	//set start freq, number of incre and freq incre
	I2C_Write(AD5933_ADDR_FREQ_REG_MSB, start_freq >> 16);	//REG 0x82
	I2C_Write(AD5933_ADDR_FREQ_REG_MMB, start_freq >> 8);	//REG 0x83
	I2C_Write(AD5933_ADDR_FREQ_REG_LSB, start_freq >> 0);	//REG 0x84

	I2C_Write(AD5933_ADDR_FICT_REG_MSB, incre_freq >> 16);	//REG 0x85
	I2C_Write(AD5933_ADDR_FICT_REG_MMB, incre_freq >> 8);	//REG 0x86
	I2C_Write(AD5933_ADDR_FICT_REG_LSB, incre_freq >> 0);	//REG 0x87

	I2C_Write(AD5933_ADDR_NICT_REG_MSB, incre_num >> 8);	//REG 0x88
	I2C_Write(AD5933_ADDR_NICT_REG_LSB, incre_num >> 0);	//REG 0x89

	I2C_Write(AD5933_ADDR_STCY_REG_MSB, cycle_set >> 8);	//REG 0x8a
	I2C_Write(AD5933_ADDR_STCY_REG_LSB, cycle_set >> 0);	//REG 0x8b

	/*I2cMsgOut1.NumOfBytes = 12;	//2+10
	I2cMsgOut1.MsgBuffer[0] = AD5933_CMD_CODE_BLOCK_WR;
	I2cMsgOut1.MsgBuffer[1] = 10;
	I2cMsgOut1.MsgBuffer[2] = start_freq >> 16;	//start frequency
	I2cMsgOut1.MsgBuffer[3] = start_freq >> 8;
	I2cMsgOut1.MsgBuffer[4] = start_freq >> 0;
	I2cMsgOut1.MsgBuffer[5] = incre_freq >> 16;	//freq increment
	I2cMsgOut1.MsgBuffer[6] = incre_freq >> 8;
	I2cMsgOut1.MsgBuffer[7] = incre_freq >> 0;
	I2cMsgOut1.MsgBuffer[8] = incre_num >> 8;	//number of increment
	I2cMsgOut1.MsgBuffer[9] = incre_num >> 0;
	I2cMsgOut1.MsgBuffer[10] = cycle_set >> 8;	//number of settling cycle
	I2cMsgOut1.MsgBuffer[11] = cycle_set >> 0;
	I2CA_WriteData(&I2cMsgOut1);*/

	ad5933_mode(stand_by);
	ad5933_mode(init_freq);
}

/*
 * ad5933 mode switch
 */
void ad5933_mode(ad5933_state_t state)
{
	//WR in reg 0x80
	I2C_Write(AD5933_ADDR_CTRL_REG_MSB, (Uint16)state);	//REG 0x80
	/*
	I2cMsgOut1.NumOfBytes = 2;	//
	I2cMsgOut1.MsgBuffer[0] = AD5933_ADDR_CTRL_REG_MSB;
	I2cMsgOut1.MsgBuffer[1] = (Uint16)state;
	I2CA_WriteData(&I2cMsgOut1);
	*/
}

/*
 * ad5933 status read.
 */
Uint16 ad5993_status(void)
{
	//set address pointer, to 0x82,
	/*
	I2cMsgOut1.NumOfBytes = 2;	//POINTER CMD and REG Addr
	I2cMsgOut1.MsgBuffer[0] = AD5933_BOARD_CMD_ADDR_PTR;
	I2cMsgOut1.MsgBuffer[1] = AD5933_ADDR_STAT_REG_MSB;
	I2CA_WriteData(&I2cMsgOut1);
	*/

	//read status
	return (I2C_Read(AD5933_ADDR_STAT_REG_MSB));
}

void I2CA_Init(void)
{
   // Initialize I2C
   I2caRegs.I2CSAR = 0x000D;        // Slave address - AD5933
   // I2CCLK = SYSCLK/(I2CPSC+1)
   #if (CPU_FRQ_40MHZ||CPU_FRQ_50MHZ)
     I2caRegs.I2CPSC.all = 4;       // Prescaler - need 7-12 Mhz on module clk
   #endif

   #if (CPU_FRQ_60MHZ)
     I2caRegs.I2CPSC.all = 6;       // Prescaler - need 7-12 Mhz on module clk
   #endif
   I2caRegs.I2CCLKL = 10;           // NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;            // NOTE: must be non zero
   I2caRegs.I2CIER.all = 0x24;      // Enable SCD & ARDY interrupts

   I2caRegs.I2CMDR.all = 0x0020;    // Take I2C out of reset
                                    // Stop I2C when suspended

   I2caRegs.I2CFFTX.all = 0x6000;   // Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;   // Enable RXFIFO, clear RXFFINT,

   return;
}

Uint16 I2CA_WriteData(struct I2CMSG *msg)
{
   Uint16 i;

   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.
   if (I2caRegs.I2CMDR.bit.STP == 1)
   {
      return I2C_STP_NOT_READY_ERROR;
   }

   // Setup slave address
   I2caRegs.I2CSAR = msg->SlaveAddress;

   // Check if bus busy
   if (I2caRegs.I2CSTR.bit.BB == 1)
   {
      return I2C_BUS_BUSY_ERROR;
   }

   // Setup number of bytes to send
   // MsgBuffer + Address
   I2caRegs.I2CCNT = msg->NumOfBytes;

   // Setup data to send
   //I2caRegs.I2CDXR = msg->MemoryHighAddr;
   //I2caRegs.I2CDXR = msg->MemoryLowAddr;
// for (i=0; i<msg->NumOfBytes-2; i++)
   for (i=0; i<msg->NumOfBytes; i++)

   {
      I2caRegs.I2CDXR = *(msg->MsgBuffer+i);
   }

   // Send start as master transmitter
   I2caRegs.I2CMDR.all = 0x6E20;

   return I2C_SUCCESS;
}

Uint16 I2CA_ReadData(struct I2CMSG *msg)
{
   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.
   if (I2caRegs.I2CMDR.bit.STP == 1)
   {
      return I2C_STP_NOT_READY_ERROR;
   }

   I2caRegs.I2CSAR = msg->SlaveAddress;

   if(msg->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP)
   {
      // Check if bus busy
      if (I2caRegs.I2CSTR.bit.BB == 1)
      {
         return I2C_BUS_BUSY_ERROR;
      }
      I2caRegs.I2CCNT = 2;
      I2caRegs.I2CDXR = msg->MemoryHighAddr;
      I2caRegs.I2CDXR = msg->MemoryLowAddr;
      I2caRegs.I2CMDR.all = 0x2620;         // Send data to setup EEPROM address
   }
   else if(msg->MsgStatus == I2C_MSGSTAT_RESTART)
   {
      I2caRegs.I2CCNT = msg->NumOfBytes;    // Setup how many bytes to expect
      I2caRegs.I2CMDR.all = 0x2C20;         // Send restart as master receiver
   }

   return I2C_SUCCESS;
}

interrupt void i2c_int1a_isr(void)     // I2C-A
{
   Uint16 IntSource, i;

   // Read interrupt source
   IntSource = I2caRegs.I2CISRC.all;

   // Interrupt source = stop condition detected
   if(IntSource == I2C_SCD_ISRC)
   {
      // If completed message was writing data, reset msg to inactive state
      if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_WRITE_BUSY)
      {
         CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
      }
      else
      {
         // If a message receives a NACK during the address setup portion of the
         // EEPROM read, the code further below included in the register access ready
         // interrupt source code will generate a stop condition. After the stop
         // condition is received (here), set the message status to try again.
         // User may want to limit the number of retries before generating an error.
         if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
         {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_SEND_NOSTOP;
         }
         // If completed message was reading EEPROM data, reset msg to inactive state
         // and read data from FIFO.
         else if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_READ_BUSY)
         {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
            for(i=0; i < I2C_NUMBYTES; i++)
            {
              CurrentMsgPtr->MsgBuffer[i] = I2caRegs.I2CDRR;
            }
         }
      }
   }  // end of stop condition detected

   // Interrupt source = Register Access Ready
   // This interrupt is used to determine when the EEPROM address setup portion of the
   // read data communication is complete. Since no stop bit is commanded, this flag
   // tells us when the message has been sent instead of the SCD flag. If a NACK is
   // received, clear the NACK bit and command a stop. Otherwise, move on to the read
   // data portion of the communication.
   else if(IntSource == I2C_ARDY_ISRC)
   {
      if(I2caRegs.I2CSTR.bit.NACK == 1)
      {
         I2caRegs.I2CMDR.bit.STP = 1;
         I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
      }
      else if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
      {
         CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_RESTART;
      }
   }  // end of register access ready
   else if(IntSource == I2C_NACK_ISRC)
   {
	   I2caRegs.I2CMDR.bit.STP = 1;
	   I2caRegs.I2CSTR.bit.NACK = 0;
   }

   // Enable future I2C (PIE Group 8) interrupts
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}
//eof
