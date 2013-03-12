/***************************************************************************//**
 *   @file   Main.c
 *   @brief  Implementation of the program's main function.
 *   @author Dan Nechita
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
 *   SVN Revision: 680
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "Communication.h"
#include "AD5933.h"

/******************************************************************************/
/*********************** Device configuration words ***************************/
/******************************************************************************/
#pragma config POSCMOD  = XT        /*!< XT oscillator mode selected */
#pragma config FNOSC    = PRIPLL    /*!< Primary Oscillator with PLL Module*/
#pragma config FPLLMUL  = MUL_20    /*!< 20x multiplier */
#pragma config FPLLIDIV = DIV_2     /*!< 2x divider */
#pragma config FPLLODIV = DIV_1     /*!< PLL output divided by 1 */
#pragma config FPBDIV   = DIV_1     /*!< PBCLK is SYSCLK divided by 1 */
#pragma config FWDTEN   = OFF       /*!< The WDT is not enabled */

/******************************************************************************/
/************************ Constants Definitions *******************************/
/******************************************************************************/
/*! List of available commands */
const char* commandsList[] = {"help?",
                              "temperature?",
                              "startFreq=",
                              "incFreq=",
                              "incNum=",
                              "sweepParam?",
                              "calibImpedance=",
                              "impedance?",
                              "currentFreq?"};
const char* commandsDescription[] = {
    "  -  Displays all available commands.",
    "  -  Displays the ambient device temperature.",
    "  -  Start frequency parameter. Accepted values: 0 - 500000Hz. ",
    "  -  Frequency increment parameter. Accepted values: 0 - 500000Hz.",
    "  -  Number of increments parameter. Accepted values: 0 - 511.",
    "  -  Displays all three sweep parameters.",
    "  -  Calibration impedance value.Accepted values: 1 - 1000000[Ohm].",
    "  -  Displays the measured impedance.",
    "  -  Displays the current frequency."};
const long  MHZ_4 = 4000000;             /*!< 16MHz / 4 */
const long  POW_2_27 = 134217728;        /*!< 2 to the power of 27 */
const long  MAX_START_FREQ = 500000;     /*!< 500 KHz maximum frequency */
const short MAX_INC_NUM = 511;           /*!< Value is represented by a 9-bit word */

/******************************************************************************/
/************************ Variables Definitions *******************************/
/******************************************************************************/
unsigned char commandsNumber = (sizeof(commandsList) / sizeof(const char*));
unsigned char receivedCommand[20];
unsigned char invalidCommand = 0;
unsigned char commandType = 0;
unsigned char command = 0;
unsigned char displayCommand = 0;
double        commandParam = 0;

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

/***************************************************************************//**
 * @brief Main function.
 *
 * @return None.
*******************************************************************************/
void main(void)
{
    /*! Variables holding information about the device */
    unsigned short temperature = 0;   /*!< Last temperature read from the device */
    unsigned long  startFreq = 0;     /*!< Start frequency sweep */
    unsigned long  incFreq = 0;       /*!< Increment frequency */
    unsigned short incNum = 0;        /*!< Number of increments */
    unsigned long  calibImped = 0;    /*!< Calibration impedance */
    double         gainFactor = 0;    /*!< Stores the value of the gain factor */
    double         impedance = 0;     /*!< Measured impedance */
    double         currentFreq = 0;   /*!< Signal frequency used during a measurement */
    /*! Temporary variables */
    unsigned char  tempString[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double         tempValue = 0;
    
    /*! Initialize the UART communication peripheral. */
    UART_Init(9600);
    /*! Initialize the AD5933 device. */
    if(AD5933_Init())
    {
        CONSOLE_WriteString("AD5933 OK");
        UART_Write(0x0D);
    }
    else
    {
        CONSOLE_WriteString("AD5933 Error");
        UART_Write(0x0D);
    }
    while(1)
    {
        CONSOLE_GetCommand(receivedCommand);
        invalidCommand = 0;
        for(command = 0; command < commandsNumber; command++)
        {
            commandType = CONSOLE_CheckCommands(receivedCommand,
                                                commandsList[command],
                                                (double*)&commandParam);
            if(commandType == 0)
            {
                invalidCommand++;
            }
            if((command == 0) && (commandType != 0))    /*!< "help?" command*/
            {
                CONSOLE_WriteString("Available commands:");
                UART_Write(0x0D);
                for(displayCommand = 0; displayCommand < commandsNumber;
                    displayCommand++)
                {
                    CONSOLE_WriteString(commandsList[displayCommand]);
                    CONSOLE_WriteString(commandsDescription[displayCommand]);
                    UART_Write(0x0D);
                }
            }
            if((command == 1) && (commandType != 0))  /*!< "temperature?" command*/
            {
                /*! Read the temperature from the device */
                temperature = AD5933_GetTemperature();
                /*! Send the requested value to user */
                CONSOLE_WriteString("temperature=");
                itoa(tempString, temperature, 10);
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString(" degrees Celsius");
                UART_Write(0xD);

            }
            if((command == 2) && (commandType != 0))  /*!< "startFreq=" command*/
            {
                /*! Check if the parameter is valid */
                if( (commandParam >= 0) && (commandParam < MAX_START_FREQ) )
                {
                    tempValue = (commandParam / MHZ_4) * POW_2_27;
                    startFreq = (unsigned long)tempValue;
                }
                else if(commandParam < 0)
                {
                    startFreq = 0;
                }
                else
                {
                    startFreq = 0x00FFFFFF;
                }
                /* Configure the sweep parameters */
                AD5933_ConfigSweep(startFreq,
                                   incFreq,
                                   incNum);
                /* Start the sweep operation */
                AD5933_StartSweep();
                /*! Send feedback to user */
                CONSOLE_WriteString(commandsList[command]);
                tempValue = ((double)startFreq * MHZ_4) / POW_2_27;
                FloatToString(tempString, tempValue);
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString(" Hz");
                UART_Write(0xD);
                /*! Update the currentFrequrncy */
                currentFreq = tempValue;
            }
            if((command == 3) && (commandType != 0))  /*!< "incFreq=" command*/
            {
                /*! Check if the parameter is valid */
                if( (commandParam >= 0) && (commandParam < MAX_START_FREQ) )
                {
                    tempValue = (commandParam / MHZ_4) * POW_2_27;
                    incFreq = (unsigned long)tempValue;
                }
                else if(commandParam < 0)
                {
                    incFreq = 0;
                }
                else
                {
                    incFreq = 0x00FFFFFF;
                }
                /* Configure the sweep parameters */
                AD5933_ConfigSweep(startFreq,
                                   incFreq,
                                   incNum);
                /* Start the sweep operation */
                AD5933_StartSweep();
                /*! Send feedback to user */
                CONSOLE_WriteString(commandsList[command]);
                tempValue = ((double)incFreq * MHZ_4) / POW_2_27;
                FloatToString(tempString, tempValue);
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString(" Hz");
                UART_Write(0xD);
            }
            if((command == 4) && (commandType != 0))  /*!< "incNum=" command*/
            {
                /*! Check if the parameter is valid */
                if( (commandParam >= 0) && (commandParam < MAX_INC_NUM) )
                {
                    incNum = (unsigned short)commandParam;
                }
                else if(commandParam < 0)
                {
                    incNum = 0;
                }
                else
                {
                    incNum = 0x01FF;
                }
                /* Configure the sweep parameters */
                AD5933_ConfigSweep(startFreq,
                                   incFreq,
                                   incNum);
                /* Start the sweep operation */
                AD5933_StartSweep();
                /*! Send feedback to user */
                CONSOLE_WriteString(commandsList[command]);
                itoa(tempString, incNum, 10);
                CONSOLE_WriteString(tempString);
                UART_Write(0xD);
            }
            if((command == 5) && (commandType != 0))  /*!< "sweepParam?" command*/
            {
                /*! Send the requested value to user */
                CONSOLE_WriteString(commandsList[2]);
                tempValue = ((double)startFreq * MHZ_4) / POW_2_27;
                FloatToString(tempString, tempValue);
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString(" Hz");
                UART_Write(0xD);
                CONSOLE_WriteString(commandsList[3]);
                tempValue = ((double)incFreq * MHZ_4) / POW_2_27;
                FloatToString(tempString, tempValue);
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString(" Hz");
                UART_Write(0xD);
                CONSOLE_WriteString(commandsList[4]);
                itoa(tempString, incNum, 10);
                CONSOLE_WriteString(tempString);
                UART_Write(0xD);
            }
            if((command == 6) && (commandType != 0))  /*!< "calibImpedance=" command*/
            {
                /*! Check if the parameter is valid */
                if( (commandParam >= 1) && (commandParam <= 1000000) )
                {
                    calibImped = (unsigned long)commandParam;
                }
                else if(commandParam < 1)
                {
                    calibImped = 1;
                }
                else
                {
                    calibImped = 1000000;
                }
                /* Calculate the gain factor for the selected impedance */
                 gainFactor = AD5933_CalculateGainFactor(calibImped,
                                                   AD5933_FUNCTION_REPEAT_FREQ);
                /*! Send feedback to user */
                CONSOLE_WriteString("Gain was calculated for Z=");
                itoa(tempString, calibImped, 10);
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString(" [Ohm]");
                UART_Write(0xD);
            }
            if((command == 7) && (commandType != 0))  /*!< "impendace?" command*/
            {
                /* Calculates the impedance between the VOUT and VIN pins. */
                impedance = AD5933_CalculateImpedance(gainFactor,
                                                   AD5933_FUNCTION_INC_FREQ);
                /*! Send the requested value to user */
                tempValue = (double)impedance / 1000;
                FloatToString(tempString, tempValue);
                CONSOLE_WriteString("impedance=");
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString("[KOhm]");
                UART_Write(0xD);
                /*! Update the currentFrequrncy */
                tempValue = ((double)incFreq * MHZ_4) / POW_2_27;
                currentFreq = currentFreq + tempValue;
            }
            if((command == 8) && (commandType != 0))  /*!< "currentFreq?" command*/
            {
                FloatToString(tempString, currentFreq);
                CONSOLE_WriteString(tempString);
                CONSOLE_WriteString(" [Hz]");
                UART_Write(0xD);
            }
        }
        if(invalidCommand == commandsNumber)
        {
            /*! Send feedback to user */
            CONSOLE_WriteString("Invalid command");
            UART_Write(0x0D);
        }
    }
}
