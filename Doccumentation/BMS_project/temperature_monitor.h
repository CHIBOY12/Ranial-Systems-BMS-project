#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

/*
  temperature_monitor.h

  This header file declares the temperature monitoring data used by the
  Battery Management System (BMS).

  The temperature values are stored in an external array so they can be
  accessed by other files in the project without creating multiple copies
  of the same data.
*/

#include "bms_config.h"   // Includes NUM_TEMP_SENSORS and other BMS configuration values

/*
  cellTemp_C

  Stores the measured temperature values from the battery pack temperature
  sensors.

  Each element in the array represents one temperature sensor reading in
  degrees Celsius.

  Example:
    cellTemp_C[0] = temperature from sensor 1
    cellTemp_C[1] = temperature from sensor 2
    cellTemp_C[2] = temperature from sensor 3

  The total number of temperature sensors is defined by NUM_TEMP_SENSORS
  in bms_config.h.

  The extern keyword means this array is declared here, but the actual
  memory for it is created in a .cpp file.
*/
extern int cellTemp_C[NUM_TEMP_SENSORS];

#endif