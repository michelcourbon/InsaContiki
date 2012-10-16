//******************************************************************************
//   MSP430 USCI I2C Transmitter and Receiver
//
//  Description: This code configures the MSP430's USCI module as 
//  I2C master capable of transmitting and receiving bytes. 
//
//  ***THIS IS THE MASTER CODE***
//
//                    Master                   
//                 MSP430F2619             
//             -----------------          
//         /|\|              XIN|-   
//          | |                 |     
//          --|RST          XOUT|-    
//            |                 |        
//            |                 |        
//            |                 |       
//            |         SDA/P3.1|------->
//            |         SCL/P3.2|------->
//
// Note: External pull-ups are needed for SDA & SCL
//
// Uli Kretzschmar
// Texas Instruments Deutschland GmbH
// November 2007
// Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
//#include "msp430x26x.h"                        // device specific header
//#include "msp430x22x4.h"
//#include "msp430x23x0.h"
//#include "msp430xG46x.h"
#include "msp430f5437.h"

#include <stdlib.h>
#include <io.h>
#include <legacymsp430.h>

#include <stdio.h>

// ...                                         // more devices are possible

#include "TI_USCI_I2C_master.h"

signed char byteCtr;
unsigned char *TI_receive_field;
unsigned char *TI_transmit_field;

//------------------------------------------------------------------------------
// void TI_USCI_I2C_receiveinit(unsigned char slave_address, 
//                              unsigned char prescale)
//
// This function initializes the USCI module for master-receive operation. 
//
// IN:   unsigned char slave_address   =>  Slave Address
//       unsigned char prescale        =>  SCL clock adjustment 
//-----------------------------------------------------------------------------
void TI_USCI_I2C_receiveinit(unsigned char slave_address, 
                             unsigned char prescale){
  //P3SEL |= SDA_PIN + SCL_PIN;                 // Assign I2C pins to USCI_B1
	P3SEL |= BIT7;
	P5SEL |= BIT4;
  UCB1CTL1 = UCSWRST;                        // Enable SW reset
  UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;       // I2C Master, synchronous mode
  UCB1CTL1 = UCSSEL_2 + UCSWRST;              // Use SMCLK, keep SW reset
  UCB1BR0 = 0x00;//prescale;                         // set prescaler
   UCB1BR1 = 62;//0;
  UCB1I2CSA = slave_address;                  // set slave address
  UCB1CTL1 &= ~UCSWRST;                       // Clear SW reset, resume operation
  UCB1IE = UCNACKIE;
  //IE2 = UCB1RXIE;                            // Enable RX interrupt
  UCB1IE |= UCRXIE;
  UCB1IE &= ~UCTXIE;
}

//------------------------------------------------------------------------------
// void TI_USCI_I2C_transmitinit(unsigned char slave_address, 
//                               unsigned char prescale)
//
// This function initializes the USCI module for master-transmit operation. 
//
// IN:   unsigned char slave_address   =>  Slave Address
//       unsigned char prescale        =>  SCL clock adjustment 
//------------------------------------------------------------------------------
void TI_USCI_I2C_transmitinit(unsigned char slave_address, 
                          unsigned char prescale){
	P3SEL |= BIT7;
	P5SEL |= BIT4;
  UCB1CTL1 = UCSWRST;                        // Enable SW reset
  UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;       // I2C Master, synchronous mode
  UCB1CTL1 = UCSSEL_2 + UCSWRST;              // Use SMCLK, keep SW reset
  UCB1BR0 = 0x00;//prescale;                         // set prescaler
  UCB1BR1 = 62;//0;
  UCB1I2CSA = slave_address;                  // Set slave address
  UCB1CTL1 &= ~UCSWRST;                       // Clear SW reset, resume operation
  UCB1IE = UCNACKIE;
  UCB1IE |= UCTXIE;//IE2 = UCB1TXIE;                            // Enable TX ready interrupt
}

//------------------------------------------------------------------------------
// void TI_USCI_I2C_receive(unsigned char byteCount, unsigned char *field)
//
// This function is used to start an I2C commuincation in master-receiver mode. 
//
// IN:   unsigned char byteCount  =>  number of bytes that should be read
//       unsigned char *field     =>  array variable used to store received data
//------------------------------------------------------------------------------
#include "sys/timetable.h"
#define i2C_BUSYWAIT_UNTIL(cond, max_time)                                  \
   {                                                                  \
    rtimer_clock_t t0;                                                  \
    t0 = RTIMER_NOW();                                                  \
    while( ( (!cond) & (RTIMER_NOW() < (t0 + max_time))  ));   \
  }
void TI_USCI_I2C_receive(unsigned char byteCount, unsigned char *field){
  TI_receive_field = field;
  if ( byteCount == 1 ){
    byteCtr = 0 ;
    //__disable_interrupt();

    UCB1CTL1 |= UCTXSTT;                      // I2C start condition
    i2C_BUSYWAIT_UNTIL(!(UCB1CTL1 & UCTXSTT),RTIMER_SECOND/100);  // Start condition sent?
    UCB1CTL1 |= UCTXSTP;                      // I2C stop condition
    //__enable_interrupt();
  } else if ( byteCount > 1 ) {

	byteCtr = byteCount - 2 ;

    UCB1CTL1 |= UCTXSTT;                      // I2C start condition
    i2C_BUSYWAIT_UNTIL(!(UCB1CTL1 & UCTXSTT),RTIMER_SECOND/100);
    //i2C_BUSYWAIT_UNTIL((byteCtr != 0),RTIMER_SECOND*8);
  } else
    while (1);                                // illegal parameter
}

//------------------------------------------------------------------------------
// void TI_USCI_I2C_transmit(unsigned char byteCount, unsigned char *field)
//
// This function is used to start an I2C commuincation in master-transmit mode. 
//
// IN:   unsigned char byteCount  =>  number of bytes that should be transmitted
//       unsigned char *field     =>  array variable. Its content will be sent.
//------------------------------------------------------------------------------
void TI_USCI_I2C_transmit(unsigned char byteCount, unsigned char *field){
  TI_transmit_field = field;
  byteCtr = byteCount;
  UCB1CTL1 |= UCTR + UCTXSTT;                 // I2C TX, start condition
}

//------------------------------------------------------------------------------
// unsigned char TI_USCI_I2C_slave_present(unsigned char slave_address)
//
// This function is used to look for a slave address on the I2C bus.  
//
// IN:   unsigned char slave_address  =>  Slave Address
// OUT:  unsigned char                =>  0: address was not found, 
//                                        1: address found
//------------------------------------------------------------------------------
unsigned char TI_USCI_I2C_slave_present(unsigned char slave_address){
  unsigned char ie2_bak, slaveadr_bak, ucB1i2cie, returnValue;
  ucB1i2cie = UCB1IE;                      // restore old UCB1I2CIE
  ie2_bak = UCB1IE;                              // store IE2 register
  slaveadr_bak = UCB1I2CSA;                   // store old slave address
  UCB1IE &= ~ UCNACKIE;                    // no NACK interrupt
  UCB1I2CSA = slave_address;                  // set slave address
  //IE2 &= ~(UCB1TXIE + UCB1RXIE);              // no RX or TX interrupts
  UCB1IE &= ~(UCRXIE +UCTXIE) ;
  __disable_interrupt();
  UCB1CTL1 |= UCTR + UCTXSTT + UCTXSTP;       // I2C TX, start condition
  while (UCB1CTL1 & UCTXSTP);                 // wait for STOP condition
  
  returnValue = !(UCB1STAT & UCNACKIFG);
  __enable_interrupt();
  UCB1IE = ie2_bak;                              // restore IE2
  UCB1I2CSA = slaveadr_bak;                   // restore old slave address
  UCB1IE = ucB1i2cie;                      // restore old UCB1CTL1
  return returnValue;                         // return whether or not 
                                              // a NACK occured
}

//------------------------------------------------------------------------------
// unsigned char TI_USCI_I2C_notready()
//
// This function is used to check if there is commuincation in progress. 
//
// OUT:  unsigned char  =>  0: I2C bus is idle, 
//                          1: communication is in progress
//------------------------------------------------------------------------------
unsigned char TI_USCI_I2C_notready(){
  return (UCB1STAT & UCBBUSY);
}
//------------------------------------------------------------------------------
// unsigned char TI_USCI_I2C_itOCCUR()
//
// This function is used to check if there is commuincation in progress.
//
// OUT:  unsigned char  =>  0: I2C bus is idle,
//                          1: communication is in progress
//------------------------------------------------------------------------------
volatile unsigned char it_has_occur;
unsigned char TI_USCI_I2C_itOCCUR(){
  if((byteCtr == 0) & (it_has_occur == 1))
  {
	  it_has_occur = 0;
	  return 1;
  }
  else
	  return 0;
}


void __attribute__((__interrupt__(USCI_B1_VECTOR))) __attribute__((section(".text")))  USCIAB1RX_ISR(void)
{

	  if (UCB1IFG & UCRXIFG){
		it_has_occur = 1;
		if ( byteCtr == 0 ){

			if (UCB1STAT & UCNACKIFG){            // send STOP if slave sends NACK
				UCB1STAT &= ~UCNACKIFG;
			  }

		  UCB1CTL1 |= UCTXSTP;                    // I2C stop condition
		  *TI_receive_field = UCB1RXBUF;
		  TI_receive_field++;
		}
		else {
		  *TI_receive_field = UCB1RXBUF;
		  TI_receive_field++;
		  byteCtr--;
		  if ( byteCtr == 0 )
			  UCB1CTL1 |= UCTXNACK;
		}
	  }
	  else {
		if (byteCtr == 0){
		  UCB1CTL1 |= UCTXSTP;                    // I2C stop condition
		  UCB1IFG &= ~UCTXIFG;                     // Clear USCI_B1 TX int flag
		}
		else {
		  UCB1TXBUF = *TI_transmit_field;
		  TI_transmit_field++;
		  byteCtr--;
		}
		if ( UCB1IFG &  UCNACKIFG){            // send STOP if slave sends NACK
			 UCB1IFG &= ~UCNACKIFG;
		  }
	  }
}
