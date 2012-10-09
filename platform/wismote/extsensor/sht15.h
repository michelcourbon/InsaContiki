/* Copyright (c) 2009  ARAGO SYSTEMS
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
  $Id: v 0.1 2011/02/15 tchapelle Exp $
*/


/**
      SHT15/75 Driver

!!!   be advise that the SHT15 and SHT75 are not i2C compliant sensors
      they are just designed to not disturb i2C devices on a 2 wire bus
      this driver allow to drive the sensor with GPIO and delay
*/
#include <stdio.h>
#include <legacymsp430.h>
#include <io.h>

/* usefull for sht15 insa sensor board modification
 *  1 for modification / O for classic configuration
 */
#define SHT15INSA 1

/* hardware configuration */

#define DATA_OUT() P3DIR |= BIT7
#define DATA_IN()  P3DIR &= ~BIT7
#define DATA_SET() P3OUT |= BIT7;  halMcuWaitUs(10)
#define DATA_CLR() P3OUT &= ~BIT7; halMcuWaitUs(10)
#define DATA_VAL() (P3IN & BIT7)

#define SCK_OUT() P5DIR |= BIT4
#define SCK_SET() P5OUT |= BIT4;  halMcuWaitUs(10)
#define SCK_CLR() P5OUT &= ~BIT4; halMcuWaitUs(10)


/***********************************************************************************
*   SHT15 functions
*/
void sht15_init();
void sht15_measure_temp();
void sht15_measure_hum();
void sht15_wait_measure();
void sht15_read_status();
void sht15_write_status();
void sht15_soft_reset();
uint16_t sht15_read16();
void sht15_write8(uint8_t val);
