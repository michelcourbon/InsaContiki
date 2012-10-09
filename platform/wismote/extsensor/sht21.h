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
#ifndef SHT21_H_
#define SHT21_H_

#define SHT21_ADDR                  0x40
#define SHT21_HUMIDITY_MESURE       0xE5
#define SHT21_TEMPERATURE_MESURE    0xE3
#define SHT21_RESET				    0xFE
#define SHT21_PRESCALER             0x3f

#include "dev/TI_USCI_I2C_master.h"
#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

/*******************************************************************************
* @fn      		sht21_retrieve_humidity
*
* @brief		get the last measure of humidity
*
*
* @param       	none
*
* @return      	unsigned int : last humidity value of the sensor
*
*/
unsigned int sht21_retrieve_humidity();

/*******************************************************************************
* @fn      		sht21_trig_humidity
*
* @brief		set the sensor to trig a humidity measure
*
*
* @param       	none
*
* @return      	none
*
*/
void sht21_trig_humidity();

/*******************************************************************************
* @fn      		sht21_retrieve_temperature
*
* @brief		get the last measure of temperature
*
*
* @param       	none
*
* @return      	unsigned int : last temperature value of the sensor
*
*/
unsigned int sht21_retrieve_temperature();

/*******************************************************************************
* @fn      		sht21_trig_temperature
*
* @brief		set the sensor to trig a temperature measure
*
*
* @param       	none
*
* @return      	none
*
*/
void sht21_trig_temperature();




#endif
