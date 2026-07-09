#ifndef BATTERY_MONITOR_H   // Prevent this header file from being included multiple times
#define BATTERY_MONITOR_H   

#include "bms_config.h"      // Include system configuration constants (such as NUM_CELLS)

// Declare the global array that stores the voltage of each battery cell.
// The actual memory for this array is allocated in battery_monitor.cpp.
// Other source files can access the latest cell voltage readings using this declaration.

extern int cellVoltage_mV[NUM_CELLS];

#endif