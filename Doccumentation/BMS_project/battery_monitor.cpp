#include "battery_monitor.h"      // Include declarations and shared definitions for the battery monitor module

// Array that stores the measured voltage of each battery cell.
// Each element corresponds to one cell in the battery pack.
// The values are stored in millivolts (mV).

int cellVoltage_mV[NUM_CELLS];