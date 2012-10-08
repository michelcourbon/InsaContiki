/*--------------------
 * purpose : this example demonstrate the accelero sensor usage
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "rtimer.h"
#include "dev/acc-sensor.h"

static unsigned int nbcount;
static int x1, y1, z1;

PROCESS(test_process, "test accelero sensor");
AUTOSTART_PROCESSES(&test_process);
 /*---------------------------------------------------------------------------*/
 PROCESS_THREAD(test_process, ev, data)
 {
	 int x2, y2, z2;
	 char buf1[100];
	 char buf[20];

	 PROCESS_BEGIN();
	 SENSORS_ACTIVATE(acc_sensor);
	 nbcount=0;
	 rtimer_clock_t start;

	 while(1)
	 {
	   nbcount++;
	   sprintf(buf1,"");
	   start = RTIMER_NOW();
	   x2 = acc_sensor.value(1);
	   y2 = acc_sensor.value(2);
	   z2 = acc_sensor.value(3);
	   if (abs(x2-x1)>=2){
		   sprintf(buf," x=%u",x2);
		   strcat(buf1,buf);
		   x1 = x2;
	   }
	   if (abs(y2-y1)>=2){
		   sprintf(buf," y=%u",y2);
		   strcat(buf1,buf);
		   y1=y2;
	   }
	   if (abs(z2-z1)>=2){
		   sprintf(buf," z=%u",z2);
		   strcat(buf1,buf);
		   z1=z2;
	   }
	   if (strlen(buf1)>0){
		   strcat(buf1,"\n");
		   printf(buf1);
		   printf("sensor event %u timer tick %u\n",nbcount,start);
	   }
	 }

	 SENSORS_DEACTIVATE(acc_sensor);
	 PROCESS_END();
 }
