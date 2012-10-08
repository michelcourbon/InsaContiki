/*
 * purpose : this example use a timer to printf every SAMPLING seconds
 */
#include <stdio.h>
#include <string.h>
#include "contiki.h"
#include "sensors.h"
#include "dev/leds.h"

static struct etimer et;
static unsigned long nbcount;

#define SAMPLING 7
#define LUM_SENSOR_EN 1
#define SHT15 1
#define CTN_SENSOR_EN 1
#define NBMOY 3

#if SHT15
#include "extsensor/sht15.h"
static int temp[NBMOY];
static int hum[NBMOY];
#endif

#if CTN_SENSOR_EN
#include "dev/ctn-sensor.h"
static int ctn[NBMOY];
#endif

#if LUM_SENSOR_EN
#include "dev/light-sensor.h"
static int lum[NBMOY];
#endif

/*
 *  mean calculation
 */
unsigned int mean( int *buffer, unsigned int nb) {
	unsigned long somme = 0;
	uint16_t i;
	for (i=0;i<nb;i++) {
		somme += buffer[i];
	}
	return somme/nb;
}

/**--------------- timer timeout handler -------------**/
static void
timeout_handler(unsigned long nbc)
{
	char buf[90];
	char buf1[50];

	uint16_t posi , value;
	posi = nbc % NBMOY;

	if (posi==(NBMOY-1)) sprintf(buf,"{\"nb\":%ld",nbc);

#if CTN_SENSOR_EN
	ctn[posi] = ctn_sensor.value(0);
	if (posi==(NBMOY-1)) {
		value = mean(ctn,NBMOY);
		sprintf(buf1, ",\"T\":%d", value);
		strcat(buf,buf1);
	}
#endif


#if LUM_SENSOR_EN
  lum[posi] = light_sensor.value(0);
	if (posi==(NBMOY-1)) {
		value = mean(lum,NBMOY);
		sprintf(buf1, ",\"L\":%d", value);
		strcat(buf,buf1);
	}
#endif

#if SHT15
		leds_on(LEDS_BLUE);
		uint16_t adc_sensor_value;
	sht15_measure_temp();       // Ask for temperature
	sht15_wait_measure();       // Wait for SHT15 to finish conversion
	adc_sensor_value = sht15_read16();// Read result

	temp[posi] = adc_sensor_value;
	if (posi==(NBMOY-1)) {
		value = mean(temp,NBMOY);
		sprintf(buf1, ",\"Ts1\":%d", value);
		strcat(buf,buf1);
	}

	sht15_measure_hum();
	sht15_wait_measure();       // Wait for SHT15 to finish conversion
	adc_sensor_value = sht15_read16();// Read result

	hum[posi] = adc_sensor_value;
	if (posi==(NBMOY-1)) {
		value = mean(hum,NBMOY);
		sprintf(buf1, ",\"Hs1\":%d", value);
		strcat(buf,buf1);
	}
	leds_off(LEDS_BLUE);
#endif

	if (posi==(NBMOY-1)) {
		strcat(buf,"}");
		printf("%s\n",buf);
	}

}

/*
 * -----------------
 */

PROCESS(test_process, "test multi sensor with mean..");
AUTOSTART_PROCESSES(&test_process);

/*
 * ----------------
 */

 PROCESS_THREAD(test_process, ev, data)
 {
   PROCESS_BEGIN();
   nbcount=0;

   /**----------- sensor init --------------**/
   #if CTN_SENSOR_EN
     SENSORS_ACTIVATE(ctn_sensor);
   #endif
   #if (LUM_SENSOR_EN)
     SENSORS_ACTIVATE(light_sensor);
   #endif
   #if SHT15
     sht15_init();
   #endif
   printf("Process multi sensors started..\n");

   while(1)
   {
	   etimer_set(&et, SAMPLING*CLOCK_SECOND);
	   PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	   timeout_handler(nbcount);
	   nbcount++;
	   etimer_restart(&et);
   }
   PROCESS_END();
 }
