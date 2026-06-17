void bmsUpdateProtection() {
  pack.faultActive = false;
  pack.chargeAllowed = true;
  pack.dischargeAllowed = true;

  for (int i = 0; i < NUM_CELLS; i++) {
    if (pack.cells[i].voltage_mV > CELL_OVERVOLTAGE_MV) {
      pack.cells[i].overVoltage = true;
      pack.chargeAllowed = false;
      pack.faultActive = true;
    }

    if (pack.cells[i].voltage_mV < CELL_UNDERVOLTAGE_MV) {
      pack.cells[i].underVoltage = true;
      pack.dischargeAllowed = false;
      pack.faultActive = true;
    }

    if (pack.cells[i].temperature_C > MAX_CELL_TEMP_C) {
      pack.cells[i].overTemp = true;
      pack.chargeAllowed = false;
      pack.dischargeAllowed = false;
      pack.faultActive = true;
    }
  }
}