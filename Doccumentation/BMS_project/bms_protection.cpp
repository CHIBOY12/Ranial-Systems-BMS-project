#include "bms_protection.h"
#include "bms_config.h"
#include "bms_data.h"

// This file handles the BMS protection logic.
// It checks for unsafe battery conditions and updates the pack fault flags.
// Protection handled here: over-voltage, under-voltage, over-temperature,
// over-current, short circuit, and charge/discharge permission.

void bmsUpdateProtection() {//
  pack.faultActive = false;
  pack.chargeAllowed = true;
  pack.dischargeAllowed = true;

  for (int i = 0; i < NUM_CELLS; i++) {
    pack.cells[i].overVoltage = false;
    pack.cells[i].underVoltage = false;
    pack.cells[i].overTemp = false;

    if (pack.cells[i].voltage_mV > CELL_OVERVOLTAGE_MV) {
      pack.cells[i].overVoltage = true;
      pack.faultActive = true;
      pack.chargeAllowed = false;
    }

    if (pack.cells[i].voltage_mV < CELL_UNDERVOLTAGE_MV) {
      pack.cells[i].underVoltage = true;
      pack.faultActive = true;
      pack.dischargeAllowed = false;
    }

    if (pack.cells[i].temperature_C > MAX_CELL_TEMP_C) {
      pack.cells[i].overTemp = true;
      pack.faultActive = true;
      pack.chargeAllowed = false;
      pack.dischargeAllowed = false;
    }
  }
    // Check for over current condition.
  if (pack.current_A > MAX_DISCHARGE_CURRENT_A) {
    pack.overCurrent = true;
    pack.faultActive = true;
    pack.dischargeAllowed = false;
  }

  // Check for short circuit condition.
  if (pack.current_A > SHORT_CIRCUIT_CURRENT_A) {
    pack.shortCircuit = true;
    pack.faultActive = true;
    pack.chargeAllowed = false;
    pack.dischargeAllowed = false;
  }

  // Store pack level over temperature status.
  pack.overTemperature = false;
  for (int i = 0; i < NUM_CELLS; i++) {
    if (pack.cells[i].overTemp) {
      pack.overTemperature = true;
    }
  }

} 9