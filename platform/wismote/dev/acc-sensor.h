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
  $Id: ACCELERO_MMA74.h,v 0.1 2011/11/22 00:00:00 tchapelle Exp $
*/
#ifndef __MMA74ACC_SENSOR_H__
#define __MMA74ACC_SENSOR_H__

#include "lib/sensors.h"
#include "contiki.h"
#include "contiki-lib.h"
#include "msp430.h"
extern const struct sensors_sensor acc_sensor;

#define MMA74ACC_SENSOR "MMA74Acc"
#define ACC_1G_DEFAULT_VALUE 25
#define X_AXIS_REGISTER 6
#define Y_AXIS_REGISTER 7
#define Z_AXIS_REGISTER 8
#define ACC_Mode_control_register 0x16
#define MEASURE_MODE    0x01
#define SENSIVITY_MODE_2G   0x08
#define SPI_3_WIRE_MODE   0x40


int ACCELERO_MMA74_get_xyz(int reg);
void ACCELERO_MMA74_init();
void ACCELERO_MMA74_test();

#endif /* __ACC_SENSOR_H__ */
