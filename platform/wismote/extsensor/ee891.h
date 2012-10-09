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
  $Id: sht21.h,v 0.1 2011/11/22 00:00:00 tchapelle Exp $
*/
#ifndef EE891_H_
#define EE891_H_

#include "dev/TI_USCI_I2C_master.h"
#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

// Registers readable
#define EE891_READ_MEASURE_VAL_3_LOW   	 	0xC0 // + bit 1 READ
#define EE891_READ_MEASURE_VAL_3_HIGH   	0xD0 // + bit 1 READ
#define EE891_READ_MEASURE_VAL_4_LOW   	 	0x70 // + bit 1 READ
#define EE891_READ_MEASURE_VAL_4_HIGH   	0x78 // + bit 1 READ

// Registers writable/readable
#define EE891_READ_FROM_CUSTOM_AREA			0x50 // + bit 1 READ
#define EE891_WRITE_TO_CUSTOM_AREA			0x10

#define EE891_BUSADDR						0xC0
#define EE891_MEASUREMENT_INTERVAL_LOW		0xC6
#define EE891_MEASUREMENT_INTERVAL_HIGH		0xC7
#define EE891_OPERATING_MODE_REG			0xD8

#define EE891_PRESCALER             		0x7f 	// Set the i2c prescaler for the SCLK



/*******************************************************************************
* @fn      		EE891_get_CO2
*
* @brief      	This function read two register of the ee891. This registers contain the low and high bits
*				of the 16 bits CO2 measure, automatically refreshed by the ee891.
*
*
* @param       	none
*
* @return      	unsigned int : last co2 value of the sensor
*
*/
unsigned int EE891_get_CO2(void);

#endif
