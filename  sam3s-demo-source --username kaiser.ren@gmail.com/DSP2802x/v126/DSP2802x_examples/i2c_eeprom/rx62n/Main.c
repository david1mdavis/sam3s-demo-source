/***************************************************************************//**
 *   @file   Main.c
 *   @brief  Implementation of the program's main function.
 *   @author Bancisor Mihai
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 531
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "YRDKRX62N.h"
#include "ST7579.h"
#include "AD5933.h"

/******************************************************************************/
/* Variables Declarations                                                     */
/******************************************************************************/
const unsigned char adiLogo [2 * 19] =
	{ 0xFF, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x07, 0x07,
	  0x0F, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F,
	  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0,
	  0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC,
	  0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF };	// ADI Logo.
unsigned char 	periodEnd	= 0;	// Indicates when the OneShot period ends.
unsigned short  temperature = 0;
unsigned long   impedanceK  = 0;
double          impedance   = 0;
double          gainFactor  = 0;

/***************************************************************************//**
 * @brief OneShot callback function.
 *
 * @param None.
 *
 * @return None.
*******************************************************************************/
void OneShotCallback(void)
{
	periodEnd = 1;
}

/***************************************************************************//**
 * @brief Creates a delay of seconds.
 *
 * @param seconds - time in seconds.
 *
 * @return None.
*******************************************************************************/
void DelaySeconds(float seconds)
{
	periodEnd = 0;
	R_TMR_CreateOneShot(PDL_TMR_UNIT0,
						PDL_TMR_OUTPUT_OFF,
						seconds,
						OneShotCallback,
						4);
	while(periodEnd == 0);
}

/***************************************************************************//**
 * @brief Main function.
 *
 * @param None.
 *
 * @return None.
*******************************************************************************/
void main(void)
{		
	YRDKRX62N_Init();
	ST7579_Init();
    ST7579_Image(2,0,adiLogo,19,16);
    ST7579_String(2,21,"ANALOG");
    ST7579_String(3,21,"DEVICES");
    ST7579_String(4,0,"wiki.analog.com");
	DelaySeconds(2);
	ST7579_Clear();
	ST7579_Image(0,0,adiLogo,19,16);	
	ST7579_String(0,22,"ST7579 OK");
    if(AD5933_Init())
    {
        ST7579_String(1,22,"AD5933 OK");
    }
    else
    {
        ST7579_String(1,22,"AD5933 Er");
    }
    temperature = AD5933_GetTemperature();
    ST7579_String(3,0,"Temperature:   C");
    ST7579_Number(3,80,temperature,2);
    /* Configure the sweep parameters */
    AD5933_ConfigSweep(0x0F5C28,
                       0x000D16,
                       0x01F4);
    /* Start the sweep operation. */
    AD5933_StartSweep();
    /* Calculate the gain factor for an impedance of 47kohms. */
    gainFactor = AD5933_CalculateGainFactor(47000,
                                            AD5933_FUNCTION_REPEAT_FREQ);
    ST7579_String(4,0,"Gain factor was");
    ST7579_String(5,0,"calc. for 47kohm");
    ST7579_String(6,0,"Impedance:  kohm");
    while (1)
    {
        /* Calculates the impedance between the VOUT and VIN pins. */
        impedance = AD5933_CalculateImpedance(gainFactor,
                                              AD5933_FUNCTION_REPEAT_FREQ);
        impedanceK = (unsigned long)impedance;
        impedanceK /= 1000;
        ST7579_Number(6,66,impedanceK,2);
    }
}
