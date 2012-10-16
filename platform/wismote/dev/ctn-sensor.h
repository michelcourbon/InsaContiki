
#ifndef __CTN_SENSOR_H__
#define __CTN_SENSOR_H__

#include "lib/sensors.h"

extern const struct sensors_sensor ctn_sensor;

#define CTN_SENSOR "CTN sensor"

// CTN power PIN P2.6/ACLK
#define ENABLE_TEMPERATURE_SENSOR() P2DIR |= BIT6;   P2OUT |= BIT6
#define SHUTDOWN_TEMPERATURE_SENSOR() P2DIR |= BIT6;   P2OUT &= ~BIT6

#endif /* __CTN_SENSOR_H__ */
