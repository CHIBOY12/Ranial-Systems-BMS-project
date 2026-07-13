#include "temperature_monitor.h"

/*
  cellTemp_C

  This array stores the temperature readings from each battery pack
  temperature sensor.

  The size of the array is set by NUM_TEMP_SENSORS, which is defined in
  bms_config.h and included through temperature_monitor.h.

  Each value is stored as an integer in degrees Celsius.

  Example:
    cellTemp_C[0] = temperature reading from sensor 1
    cellTemp_C[1] = temperature reading from sensor 2

  This line is the actual definition of the array. The matching extern
  declaration is located in temperature_monitor.h, which allows other files
  to access this same array without creating duplicate copies.
*/
int cellTemp_C[NUM_TEMP_SENSORS];