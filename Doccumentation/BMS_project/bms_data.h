#ifndef BMS_DATA_H
#define BMS_DATA_H

/*
  bms_data.h

  This file defines the main data structures used by the BMS software.

  organizes and stores battery cell data and full pack data
  so the rest of the program can use the same shared information.
*/

#include "bms_config.h"  // Gives access to NUM_CELLS and other project-wide settings

/*
  CellData

  Stores information for one individual battery cell.
  Since this is a 4S battery project, the program will create
  one CellData object for each cell in the pack.
*/
struct CellData {
  int voltage_mV;      // Cell voltage in millivolts, example: 3700 mV = 3.7 V
  int temperature_C;   // Cell temperature in degrees Celsius

  bool overVoltage;    // True if this cell is above the safe maximum voltage
  bool underVoltage;   // True if this cell is below the safe minimum voltage
  bool overTemp;       // True if this cell is above the safe temperature limit
};

/*
  PackData

  Stores information for the entire battery pack.

  This includes:
  - all individual cell data
  - total pack voltage
  - pack current
  - pack-level fault conditions
  - min/max cell voltage
  - whether charging and discharging are allowed
*/
struct PackData {
  CellData cells[NUM_CELLS];  // Array holding data for each cell in the battery pack

  int packVoltage_mV;         // Total pack voltage in millivolts
  float current_A;            // Pack current in amps

  bool overCurrent;           // True if pack current is above the safe current limit
  bool shortCircuit;          // True if a short-circuit condition is detected
  bool overTemperature;       // True if the pack has an overtemperature condition

  int minCellVoltage_mV;      // Lowest cell voltage currently measured
  int maxCellVoltage_mV;      // Highest cell voltage currently measured

  bool chargeAllowed;         // True if charging is allowed
  bool dischargeAllowed;      // True if discharging is allowed
  bool faultActive;           // True if any fault is active in the BMS
};

/*
  Global pack data object.

  The actual variable is created in bms_data.cpp.
  The extern keyword lets other files use the same shared pack object
  without creating duplicate copies.
*/
extern PackData pack;

#endif