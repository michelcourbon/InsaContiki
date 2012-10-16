
#include "contiki.h"
#include "lib/sensors.h"
#include "dev/ctn-sensor.h"

const struct sensors_sensor ctn_sensor;
static uint8_t active;

	/*---------------------------------------------------------------------------*/
	static int
	value(int type)
	{
	  ADC12IFG &= ~ADC12IFG0;        // Clear "conversion finished" Interrupt Flag
	  ADC12CTL0 |= ADC12SC;          // Start sampling/conversion
	  while(!(ADC12IFG & ADC12IFG0)); // When sampling is over
	  return ADC12MEM0;
	}
	/*---------------------------------------------------------------------------*/
	static int
	status(int type)
	{
	  switch(type) {
	  case SENSORS_ACTIVE:
	  case SENSORS_READY:
	    return active;
	  default:
	    return 0;
	  }
	}
	/*---------------------------------------------------------------------------*/
	static int
	configure(int type, int c)
	{
	  switch(type) {
	  case SENSORS_ACTIVE:
	    if(c) {
	      if(!status(SENSORS_ACTIVE)) {
	        ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
	        ADC12CTL1 = ADC12SHP;                     // Use sampling timer
	        ADC12MCTL0 |= ADC12INCH2; // THERMORESISTANCE_CHANNEL;
	        P2DIR |= BIT6;   P2OUT &= ~BIT6;    // shutdown off
	        P6SEL |= BIT6;      // P6.6 ADC option select CTN
	        P6DIR &= BIT6;    // P6.6 as Input
	        ADC12CTL0 |= ADC12ENC;  // Enable Conversion (ADC12_A enabled)
	      }
	    } else {
	    }
	    break;
	  }
	  return 0;
	}
	/*---------------------------------------------------------------------------*/
	SENSORS_SENSOR(ctn_sensor, CTN_SENSOR, value, configure, status);

