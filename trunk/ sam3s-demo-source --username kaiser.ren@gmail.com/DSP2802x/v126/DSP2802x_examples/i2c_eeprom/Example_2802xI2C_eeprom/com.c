/*
 * com.c
 *
 *  Created on: 2013-1-25
 *      Author: kren
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

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
    SciaRegs.SCIFFCT.all=0x0;

}

/*
 * Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
 */
void scia_echoback_init()
{
	// For this example, only init the pins for the SCI-A port.
	// This function is found in the DSP2802x_Sci.c file.
	   InitSciaGpio();

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
        SciaRegs.SCIHBAUD    =0x0000;  // 9600 baud @LSPCLK = 15MHz (60 MHz SYSCLK).
        SciaRegs.SCILBAUD    =0x00C2;
    #elif (CPU_FRQ_50MHZ)
        SciaRegs.SCHBAUD     =0x0000;  // 9600 baud @LSPCLK = 12.5 MHz (50 MHz SYSCLK)
    #elif (CPU_FRQ_40MHZ)    =0x00A1;
        SciaRegs.SCIHBAUD    =0x0000;  // 9600 baud @LSPCLK = 10MHz (40 MHz SYSCLK).
        SciaRegs.SCILBAUD    =0x0081;
    #endif

    SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset

    /* Init scia fifo. */
    scia_fifo_init();
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

//eof
