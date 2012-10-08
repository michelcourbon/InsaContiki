/*--------------------
 * purpose : this example use a timer to printf every SAMPLING seconds
 *  temperature and humidity raw value...
 *  to convert in real value please verify the alim tension to obtain exact coefficient
 *  the string use a json format type
 */
#include <stdio.h>
#include <string.h>
#include "contiki.h"

static struct etimer et;
static int nbcount;

#define SAMPLING 5
#define SHT15 1

#if SHT15
#include "sht15.h"
#endif

/**--------------- timer timeout handler -------------**/
static void
timeout_handler(int nbc)
{
	char buf[80];
	char buf1[50];
	sprintf(buf,"{\"count\":%d,",nbc);

#if SHT15
	uint16_t adc_sensor_value;
	sht15_measure_temp();       // Ask for humidity value
	sht15_wait_measure();       // Wait for SHT15 to finish conversion
	adc_sensor_value = sht15_read16();// Read result
	sprintf(buf1, "\"Ts1\":%d", adc_sensor_value);
	strcat(buf,buf1);
	sht15_measure_hum();
	sht15_wait_measure();       // Wait for SHT15 to finish conversion
	adc_sensor_value = sht15_read16();// Read result
	sprintf(buf1, ",\"Hs1\":%d", adc_sensor_value);
	strcat(buf,buf1);
#endif
	strcat(buf,"}");

	printf("%s\n",buf);
}


PROCESS(test_process, "test sht15 Insa");
AUTOSTART_PROCESSES(&test_process);
 /*---------------------------------------------------------------------------*/

 PROCESS_THREAD(test_process, ev, data)
 {
   PROCESS_BEGIN();
   nbcount=0;

#if SHT15
  sht15_init();
#endif

   while(1)
   {
	   etimer_set(&et, SAMPLING*CLOCK_SECOND);
	   PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	   nbcount++;
	   timeout_handler(nbcount);
	   etimer_restart(&et);
   }
   PROCESS_END();
 }
