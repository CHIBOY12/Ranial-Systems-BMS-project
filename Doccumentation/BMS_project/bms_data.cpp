#include "bms_data.h"    // Include the battery data structure definitions

//------------------------------------------------------------
// Global Battery Pack Data
//------------------------------------------------------------
// This object stores all battery information for the entire
// Battery Management System (BMS).
//
// It contains:
// - Cell voltages
// - Cell temperatures
// - Current
// - Pack voltage
// - Protection status
// - Charge/discharge permissions
//
// Every module in the project shares and updates this object.
//------------------------------------------------------------

PackData pack;