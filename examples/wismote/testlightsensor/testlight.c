/*--------------------
 * purpose : this example use a timer to printf every SAMPLING seconds
 *  the event count and light sensor ADC value
 *  the result is a integrated 4 measures value
 *  the result string is formatted in simple json format
 */
#include <stdio.h>
#include "contiki.h"

#include "sensors.h"
#include "dev/light-sensor.h"
#include "dev/leds.h"

static struct etimer et;
static int nbcount;

#define SAMPLING 7

PROCESS(test_process, "test light Process");
AUTOSTART_PROCESSES(&test_process);
 /*---------------------------------------------------------------------------*/
 PROCESS_THREAD(test_process, ev, data)
 {
   PROCESS_BEGIN();
   SENSORS_ACTIVATE(light_sensor);
   nbcount=0;
   uint16_t light_value;
   int i;

   while(1)
   {
	   etimer_set(&et, SAMPLING*CLOCK_SECOND);
	   PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	   nbcount++;
	   light_value = 0;
	   for (i=0;i<4;i++){
		   light_value += light_sensor.value(0);
		   clock_delay(20);
	   }
	   leds_on(LEDS_RED);
	   printf("{\"count\":%u,\"light\":%u}\n",nbcount,light_value);
	   leds_off(LEDS_RED);
   }
   SENSORS_DEACTIVATE(light_sensor);
   PROCESS_END();
 }
