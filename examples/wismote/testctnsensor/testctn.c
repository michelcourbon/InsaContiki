/*--------------------
 * purpose : this example use a timer to printf every SAMPLING seconds
 *  the event count and ctn sensor ADC value
 *  the result is a integrated 4 measures value
 *  the result string is formatted in simple json format
 */

#include <stdio.h>
#include "contiki.h"

#include "sensors.h"
#include "dev/ctn-sensor.h"
#include "dev/leds.h"

static struct etimer et;
static int nbcount;

#define SAMPLING 7

PROCESS(test_process, "test ctn Process");
AUTOSTART_PROCESSES(&test_process);
 /*---------------------------------------------------------------------------*/
 PROCESS_THREAD(test_process, ev, data)
 {
   PROCESS_BEGIN();
   SENSORS_ACTIVATE(ctn_sensor);
   nbcount=0;
   uint16_t ctn_value;
   int i;

   while(1)
   {
	   etimer_set(&et, SAMPLING*CLOCK_SECOND);
	   PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	   nbcount++;
	   ctn_value = 0;
	   for (i=0;i<4;i++){
		   ctn_value += ctn_sensor.value(0);
		   clock_delay(80);
	   }
	   printf("{\"count\":%u,\"ctn\":%u}\n",nbcount,ctn_value);
	   leds_off(LEDS_RED);
   }
   SENSORS_DEACTIVATE(ctn_sensor);
   PROCESS_END();
 }
