#include "collect-view.h"
#include "collect-view-wismote.h"

#include "sensors.h"
#include "dev/ctn-sensor.h"
#include "dev/light-sensor.h"

/* sensor initializing process */
void sensor_init (void) {
  SENSORS_ACTIVATE(ctn_sensor);
  SENSORS_ACTIVATE(light_sensor);
}

/*---------------------------------------------------------------------------*/
void
collect_view_arch_read_sensors(struct collect_view_data_msg *msg)
{
  static int initialized = 0;

  if(!initialized) {
    sensor_init();
    initialized = 1;
  }

  msg->sensors[BATTERY_VOLTAGE_SENSOR] = 0;
  msg->sensors[BATTERY_INDICATOR] = 0;
  msg->sensors[LIGHT1_SENSOR] = light_sensor.value(0);
  msg->sensors[LIGHT2_SENSOR] = 0;
  msg->sensors[TEMP_SENSOR] = ctn_sensor.value(0);
  msg->sensors[HUMIDITY_SENSOR] = 0;

}
/*---------------------------------------------------------------------------*/
