#include <stdio.h>
#include "contiki.h"

#include "dev/button-sensor.h"

static unsigned int nbtours=0;

PROCESS(compteur_process, "button evt counter Process");
 AUTOSTART_PROCESSES(&compteur_process);
 /*---------------------------------------------------------------------------*/
 PROCESS_THREAD(compteur_process, ev, data)
 {
   PROCESS_BEGIN();
   SENSORS_ACTIVATE(button_sensor);

   while(1)
   {
	 PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &button_sensor);
	 nbtours += 1;
	 printf("user button pressed %d times\n",nbtours);
   }
   SENSORS_DEACTIVATE(button_sensor);
   PROCESS_END();
 }
