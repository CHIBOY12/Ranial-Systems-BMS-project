#ifndef BQ76952_DRIVER_H
#define BQ76952_DRIVER_H

#include <Arduino.h>
#include "bms_config.h"

int16_t bq76952ReadWord(uint8_t command);

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

bool bq76952WriteDataMemory(uint16_t address, uint8_t value);
bool bq76952WaitForConfigUpdate();
bool bq76952ConfigureThermistors();
bool bq76952ConfigureCurrentProtection();
bool bq76952Initialize();

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
