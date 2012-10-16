#ifndef USCI_LIB
#define USCI_LIB

#define SDA_PIN 0x02                                  // msp430x261x UCB0SDA pin
#define SCL_PIN 0x04                                  // msp430x261x UCB0SCL pin

#include "sys/timetable.h"
#define i2C_BUSYWAIT_UNTIL(cond, max_time)                                  \
   {                                                                  \
    rtimer_clock_t t0;                                                  \
    t0 = RTIMER_NOW();                                                  \
    while( ( (!cond) & (RTIMER_NOW() < (t0 + max_time))  ));   \
  }			// 1 => ! 0 => !( 0 & 0 ) while( !( (cond) & RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + (max_time)) ) ){printf("RTIMER_NOW() %d ,t0 + max_time %d\n\r",RTIMER_NOW(),t0 + max_time); };


void TI_USCI_I2C_receiveinit(unsigned char slave_address, unsigned char prescale);
void TI_USCI_I2C_transmitinit(unsigned char slave_address, unsigned char prescale);


void TI_USCI_I2C_receive(unsigned char byteCount, unsigned char *field);
void TI_USCI_I2C_transmit(unsigned char byteCount, unsigned char *field);


unsigned char TI_USCI_I2C_slave_present(unsigned char slave_address);
unsigned char TI_USCI_I2C_notready();
unsigned char TI_USCI_I2C_itOCCUR();


#endif
