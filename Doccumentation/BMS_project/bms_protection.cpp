#include "bms_protection.h"
#include "bms_config.h"
#include "bms_data.h"

void bmsUpdateProtection() {
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
}