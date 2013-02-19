/*
 * com.c
 *
 *  Created on: 2012-11-26
 *      Author: cui
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdio.h>

/**********************************************************
 * 				Macro
 **********************************************************/

/**********************************************************
 * 				prototype
 **********************************************************/
// Prototype statements for functions found within this file.
void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);
void FloatToString(char * buf, double val);
static unsigned char btoh( unsigned char num );
void scia_Byte2Hex( Uint16 byte );
void scia_Byte2Decimal( Uint16 byte );
void scia_PrintLF( void );
Uint16 scia_read(void);
/**********************************************************
 * 				Global Variable
 **********************************************************/

/**********************************************************
 * 				function
 **********************************************************/
/*
 * Initalize the SCI FIFO
 */
void scia_fifo_init(void)
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    //SciaRegs.SCIFFRX.all=0x0000;
    SciaRegs.SCIFFCT.all=0x0;

}

/*
 * Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
 */
void scia_echoback_init(void)
{
	// For this example, only init the pins for the SCI-A port.
	// This function is found in the DSP2802x_Sci.c file.
	InitSciaGpio();

	/* Init scia fifo. */
	scia_fifo_init();

    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

    SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA =1;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;

    // SCI BRR = LSPCLK/(SCI BAUDx8) - 1
    #if (CPU_FRQ_60MHZ)
        //SciaRegs.SCIHBAUD    =0x0000;  // 9600 baud @LSPCLK = 15MHz (60 MHz SYSCLK).
        //SciaRegs.SCILBAUD    =0x00C2;	// 9600 baud @LSPCLK = 15MHz (60 MHz SYSCLK).
        SciaRegs.SCIHBAUD    =0x0000;  // 38400 baud @LSPCLK = 15MHz (60 MHz SYSCLK).
        SciaRegs.SCILBAUD    =0x0030;	// 38400 baud @LSPCLK = 15MHz (60 MHz SYSCLK).
    #elif (CPU_FRQ_50MHZ)
        SciaRegs.SCHBAUD     =0x0000;  // 9600 baud @LSPCLK = 12.5 MHz (50 MHz SYSCLK)
    #elif (CPU_FRQ_40MHZ)    =0x00A1;
        SciaRegs.SCIHBAUD    =0x0000;  // 9600 baud @LSPCLK = 10MHz (40 MHz SYSCLK).
        SciaRegs.SCILBAUD    =0x0081;
    #endif

    SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}

/*
 * Transmit a character from the SCI
 */
void scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF=a;

}

/*
 * Print a string for debug or any purpose.
 */
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

/*
 * Get a char
 */
Uint16 scia_read(void)
{
	while(SciaRegs.SCIFFRX.bit.RXFFST !=1) { } // wait for XRDY =1 for empty state
	return (SciaRegs.SCIRXBUF.all);
}

static unsigned char btoh( unsigned char num )
{
   num = num & 0x0F;
   return ( num<10 )? num+'0' : num-10+'A';
}

/*
 * print uint16 to hex style
 */
void scia_Byte2Hex( Uint16 byte )
{
	unsigned char c;
	int i;
	Uint16 digit;

	scia_xmit( '0' );
	scia_xmit( 'x' );
	for (i = 3; i >= 0; i--)
	{
	    digit = (byte >> (i * 4)) & 0xf;
	    c = btoh( digit );
	    scia_xmit( c );
	}
	scia_xmit( ' ' );
}
/*
 * print "/r/n"
 */
void scia_PrintLF( void )
{
	scia_msg("\r\n");
}
/***************************************************************************//**
 * @brief Converts a float value to a character array with 3 digits of accuracy.
 *
 * @param *buf - returns the converterd value
 * @param val - value to be converted
 *
 * @return None.
*******************************************************************************/
void FloatToString(char * buf, double val)
{
    long  intPart  = 0;
    short fracPart = 0;
    char  charPos  = 0;
    char  localBuf[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char  i = sizeof(localBuf) - 1;

    intPart = (long)val;
    fracPart = (short)((val - intPart) * 1000 + 0.5);
    while(i > (sizeof(localBuf) - 4))
    {
        localBuf[i] = (fracPart % 10) + 0x30;
        fracPart /= 10;
        i--;
    }
    localBuf[i] = '.';
    if(intPart == 0)
    {
        i --;
        localBuf[i] = '0';
    }
    while(intPart)
    {
        i --;
        localBuf[i] =(intPart % 10)  + 0x30;
        intPart /= 10;
    }
    for(charPos = i; charPos < sizeof(localBuf); charPos ++)
    {
        *buf = localBuf[charPos];
        buf ++;
    }
    *buf = 0;
}
//eof
