/* Copyright (c) 2011  ARAGO SYSTEMS
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/
/*
  $Id: sht21.c,v 0.1 2011/11/22 00:00:00 tchapelle Exp $
*/
#include "ee891.h"



volatile unsigned char result[4]; 				// Local to store the result

/*******************************************************************************
* @fn      		EE891_get_CO2
*
* @brief		This function read two register of the ee891. This registers contain the low and high bits
*				of the 16 bits CO2 measure automatically refreshed by the ee891.
*
* @param       	none
*
* @return      	unsigned int : last CO2 in pppm
*
*/
unsigned int EE891_get_CO2(void)
{
	TI_USCI_I2C_receiveinit(EE891_READ_MEASURE_VAL_4_LOW,EE891_PRESCALER); 	// initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(2,&result[0]);										// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 			// wait for bus to be free
	i2C_BUSYWAIT_UNTIL((TI_USCI_I2C_itOCCUR()),RTIMER_SECOND );
	//while(!TI_USCI_I2C_itOCCUR());

	TI_USCI_I2C_receiveinit(EE891_READ_MEASURE_VAL_4_HIGH,EE891_PRESCALER); // initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(2,&result[2]);										// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 			// wait for bus to be free
	i2C_BUSYWAIT_UNTIL((TI_USCI_I2C_itOCCUR()),RTIMER_SECOND );
	//while(!TI_USCI_I2C_itOCCUR());

	return ( ((result[2] << 8) & 0xFF00) + (result[0] & 0xFF));
}

unsigned int ee891_read_gain(void)
{
	unsigned char array[5];

	TI_USCI_I2C_receiveinit(0x08,EE891_PRESCALER); 	// initialize USCI to read, set i2c slave adress//TI_USCI_I2C_receiveinit(EE891_READ_FROM_CUSTOM_AREA,EE891_PRESCALER); 	// initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(2,&result[0]);							// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be freei2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND/100 ); 	// wait for bus to be free

	TI_USCI_I2C_receiveinit(0x20,EE891_PRESCALER); 	// initialize USCI to read, set i2c slave adress//TI_USCI_I2C_receiveinit(EE891_READ_FROM_CUSTOM_AREA,EE891_PRESCALER); 	// initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(2,&result[2]);							// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be freei2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND/100 ); 	// wait for bus to be free

	return result[0] + ((result[2]<< 8) & 0xFF00);
}
