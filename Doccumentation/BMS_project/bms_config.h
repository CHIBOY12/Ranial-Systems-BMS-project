#ifndef BMS_CONFIG_H    // Prevent multiple inclusions of this header file
#define BMS_CONFIG_H

//------------------------------------------------------------
// Battery Pack Configuration
//------------------------------------------------------------


#define NUM_CELLS 4          // Number of battery cells connected in series
#define NUM_TEMP_SENSORS 7   // Number of temperature sensors (thermistors) used

//------------------------------------------------------------
// Voltage Protection Thresholds (millivolts)
//------------------------------------------------------------

// Maximum safe voltage for each battery cell
// Charging will be disabled if a cell exceeds this value.
#define CELL_OVERVOLTAGE_MV 4200



// Minimum safe voltage for each battery cell
// Discharging will be disabled if a cell drops below this value.
#define CELL_UNDERVOLTAGE_MV 3000

//------------------------------------------------------------
// Temperature Protection Thresholds (degrees Celsius)
//------------------------------------------------------------

// Maximum allowable battery temperature
// Charging and discharging will stop above this temperature.
#define MAX_CELL_TEMP_C 60


// Minimum allowable battery temperature
// Can be used to prevent charging below freezing.
#define MIN_CELL_TEMP_C 0


//------------------------------------------------------------
// Current Protection Thresholds (Amps)
//------------------------------------------------------------

// Maximum continuous discharge current
// If exceeded, an over-current fault is generated.
#define MAX_DISCHARGE_CURRENT_A 10.0


// Short circuit current threshold
// If exceeded, the battery pack is immediately protected.
#define SHORT_CIRCUIT_CURRENT_A 30.0

#endif