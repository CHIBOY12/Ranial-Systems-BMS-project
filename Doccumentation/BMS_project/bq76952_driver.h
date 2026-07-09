#ifndef BQ76952_DRIVER_H
#define BQ76952_DRIVER_H

/*
  bq76952_driver.h

  This header file lists the functions used to communicate with the BQ76952
  battery monitor IC.

 
*/

#include <Arduino.h>      // Gives access to Arduino data types like uint16_t and bool
#include "bms_config.h"   // Gives access to project settings like NUM_CELLS and NUM_TEMP_SENSORS

/*
  Reads the voltage of each battery cell from the BQ76952.

  The measured values are stored in the cellVoltage_mV array.
  Each value should be in millivolts.


*/
void bq76952ReadCellVoltages(int cellVoltage_mV[]);

/*
  Reads the total pack voltage from the BQ76952.

  The result is stored in packVoltage_mV.
  The value should represent the full battery pack voltage in millivolts.
*/
void bq76952ReadPackVoltage(int &packVoltage_mV);

/*
  Reads the charge or discharge current from the BQ76952.

  The result is stored in current_A.
  Positive or negative current direction depends on how the shunt resistor
  and BQ76952 current-sense pins are configured.
*/
void bq76952ReadCurrent(float &current_A);

/*
  Reads temperature values from the BQ76952.

  The measured values are stored in the cellTemp_C array.
  Each value should be in degrees Celsius.
*/
void bq76952ReadTemperatures(int cellTemp_C[]);

/*
  Reads the BQ76952 protection status.

  This function should return a 16-bit value containing fault/protection flags.
  These flags can be used to detect conditions like overvoltage, undervoltage,
  overcurrent, or overtemperature.
*/
uint16_t bq76952ReadProtectionStatus();

/*
  Sends a subcommand to the BQ76952.

  Subcommands are used for BQ76952 actions that are not simple direct register reads.
  Examples can include enabling FET control, resetting counters, or entering
  specific device modes.
*/
void bq76952SendSubcommand(uint16_t subcommand);

/*
  Controls the BQ76952 charge and discharge FETs.

  chargeEnable:
    true  = allow charging
    false = disable charging

  dischargeEnable:
    true  = allow discharging
    false = disable discharging
*/
void bq76952SetFETs(bool chargeEnable, bool dischargeEnable);

/*
  Controls cell balancing.

  balanceMask is a bitmask.
  Each bit represents whether balancing should be enabled for a cell.

  Example for 4 cells:
  bit 0 = Cell 1
  bit 1 = Cell 2
  bit 2 = Cell 3
  bit 3 = Cell 4

  If balanceMask = 0b0010, then Cell 2 balancing is requested.
*/
void bq76952SetBalancing(uint16_t balanceMask);

#endif