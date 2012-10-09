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
#include "sht21.h"

volatile unsigned char result[3]; 				// Local to store the result
volatile unsigned char result2[3]; 				// Local to store the result

/***************************************/
void sht21_trig_humidity()
{
	unsigned char array[5];

	// Power the SHT21
	P6DIR |= BIT0;
	P6OUT |= BIT0;

	P3DIR |= BIT5;
	P3OUT |= BIT5;

	array[0] = SHT21_HUMIDITY_MESURE; 	// set i2c command (trig humidity or temperature)

	TI_USCI_I2C_transmitinit(SHT21_ADDR,SHT21_PRESCALER); // initialize USCI to write, set i2c slave adress
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be free

	TI_USCI_I2C_transmit(1,&array); 		// transmit the first bytes
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND );
}
unsigned int sht21_retrieve_humidity()
{

	TI_USCI_I2C_receiveinit(SHT21_ADDR,SHT21_PRESCALER); 	// initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(3,&result);							// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be freei2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND/100 ); 	// wait for bus to be free

	while((UCB1STAT & UCSCLLOW));
	while(!TI_USCI_I2C_itOCCUR());

	return (((result[0]<< 8) & 0xFF00) + result[1]);
}
void sht21_trig_temperature()
{
	unsigned char array2[5];

	// Power the SHT21
	P6DIR |= BIT0;
	P6OUT |= BIT0;

	P3DIR |= BIT5;
	P3OUT |= BIT5;


	array2[0] = SHT21_TEMPERATURE_MESURE; 	// set i2c command (trig humidity or temperature)

	TI_USCI_I2C_transmitinit(SHT21_ADDR,SHT21_PRESCALER); // initialize USCI to write, set i2c slave adress
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be free

	TI_USCI_I2C_transmit(1,&array2); 		// transmit the first bytes
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND );
}
unsigned int sht21_retrieve_temperature()
{

	TI_USCI_I2C_receiveinit(SHT21_ADDR,SHT21_PRESCALER); 	// initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(3,&result);							// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be freei2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND/100 ); 	// wait for bus to be free

	while((UCB1STAT & UCSCLLOW));
	while(!TI_USCI_I2C_itOCCUR());

	return (((result[0]<< 8) & 0xFF00) + result[1]);
}
/***************************************/

int sht21_get_humidity(void)
{

   unsigned char array[5];

	// Power the SHT21
	P3DIR |= BIT5;
	P3OUT |= BIT5;

	array[0] = SHT21_HUMIDITY_MESURE; 	// set i2c command (trig humidity or temperature)

	TI_USCI_I2C_transmitinit(SHT21_ADDR,SHT21_PRESCALER); // initialize USCI to write, set i2c slave adress
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be free

	TI_USCI_I2C_transmit(1,&array); 		// transmit the first bytes
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND );


	TI_USCI_I2C_receiveinit(SHT21_ADDR,SHT21_PRESCALER); 	// initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(3,&result);							// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be freei2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND/100 ); 	// wait for bus to be free

	while((UCB1STAT & UCSCLLOW));
	while(!TI_USCI_I2C_itOCCUR());

	return (((result[0]<< 8) & 0xFF00) + result[1]);
}


/*
 *
 */
int sht21_get_temperature(void)
{
	unsigned char array2[5];

	// Power the SHT21
	P3DIR |= BIT5;
	P3OUT |= BIT5;

	array2[0] = SHT21_TEMPERATURE_MESURE; 	// set i2c command (trig humidity or temperature)

	TI_USCI_I2C_transmitinit(SHT21_ADDR,SHT21_PRESCALER); // initialize USCI to write, set i2c slave adress
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be free

	TI_USCI_I2C_transmit(1,&array2); 		// transmit the first bytes
	i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND );


	TI_USCI_I2C_receiveinit(SHT21_ADDR,SHT21_PRESCALER); 	// initialize USCI to read, set i2c slave adress
	TI_USCI_I2C_receive(3,&result2);							// read i2c result
	i2C_BUSYWAIT_UNTIL(!(TI_USCI_I2C_notready()),RTIMER_SECOND ); 	// wait for bus to be freei2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND/100 ); 	// wait for bus to be free

	while((UCB1STAT & UCSCLLOW));
	while(!TI_USCI_I2C_itOCCUR());

	return (((result2[0]<< 8) & 0xFF00) + result2[1]);
}
