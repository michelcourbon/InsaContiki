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
  $Id: ACCELERO_MMA74.c,v 0.1 2011/11/22 00:00:00 tchapelle Exp $
*/

#include "dev/acc-sensor.h"
#include "TI_USCI_I2C_master.h"

/*---------------------------------------------------------------------------*/

const struct sensors_sensor acc_sensor;
static uint8_t active;

/*---------------------------------------------------------------------------*/
static void
activate(void)
{
  ACCELERO_MMA74_init();
  active = 1;
}
/*---------------------------------------------------------------------------*/
static void
deactivate(void)
{
  active = 0;
}
/*---------------------------------------------------------------------------*/
static int
value(int type)
{
  if (type == 1)
	  return ACCELERO_MMA74_get_xyz(X_AXIS_REGISTER);
  if (type == 2)
	  return ACCELERO_MMA74_get_xyz(Y_AXIS_REGISTER);
  if(type == 3)
	  return ACCELERO_MMA74_get_xyz(Z_AXIS_REGISTER);
  else
	  return 0;
}
/*---------------------------------------------------------------------------*/
static int
configure(int type, int c)
{
  switch(type) {
  case SENSORS_ACTIVE:
    if (c) {
      activate();
    } else {
      deactivate();
    }
    break;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
static int
status(int type)
{
  switch (type) {
  case SENSORS_ACTIVE:
  case SENSORS_READY:
    return active;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(acc_sensor, MMA74ACC_SENSOR,
	       value, configure, status);

/*--------------------------------------------------------------------
 *  specific for wismote platform
 *  using MMA74
 */
int ACCELERO_MMA74_get_xyz(int reg)
{
	int axe_value;
	UCB1CTL1 = UCSSEL_2 + UCSWRST;	// Use SMCLK, keep SW reset
	UCB1CTL1 &= ~UCSWRST;         	// Clear SW reset, resume operation
	UCB1CTL1 |= UCTXSTT + UCTR;    	// I2C TX, start condition

	UCB1IFG &= ~UCTXIFG;
	UCB1TXBUF = reg; 		// Select register axes
	while(!(UCTXIFG & UCB1IFG));

	UCB1IFG &= ~UCRXIFG;
	UCB1CTL1 &= ~UCTR ;		// Read mode
	
	UCB1CTL1 |= UCTXSTT;            // I2C RX, start condition

	while(!(UCRXIFG & UCB1IFG));
	
	UCB1CTL1 |= UCTXSTP;		// STOP
	
	axe_value = UCB1RXBUF;
	while (UCB1STAT & UCBBUSY); // wait for bus to be free
	//while ( TI_USCI_I2C_notready() ); // wait for bus to be free

	if(axe_value > 0x7F)
		return (128 -  (axe_value & 0x7F));
	else
		return axe_value;
}

/*******************************************************************************
* @fn         ACCELERO_MMA74_init
*
* @brief    initialize i2c and slave address
*
*
* @param        none
*
* @return       none
*
*/
void ACCELERO_MMA74_init()
{
  UCB0I2COA = 0x48;             // own address
  unsigned char array[5];
  TI_USCI_I2C_transmitinit(0x1D,0x3f);// initialize USCI
  while ( TI_USCI_I2C_notready() );   // wait for bus to be free

  //__disable_interrupt();
  array[0] = ACC_Mode_control_register;   // set i2c command
  array[1] = MEASURE_MODE | SENSIVITY_MODE_2G | SPI_3_WIRE_MODE;  // set i2c command

  TI_USCI_I2C_transmit(2,&array);     // transmit the first bytes
  i2C_BUSYWAIT_UNTIL( !(TI_USCI_I2C_notready()),RTIMER_SECOND );
}
