void bmsUpdateBalancing() {
  uint16_t balanceMask = 0;

  for (int i = 0; i < NUM_CELLS; i++) {
    if (pack.cells[i].voltage_mV > pack.minCellVoltage_mV + 20) {
      balanceMask |= (1 << i);
      pack.cells[i].balanceEnabled = true;
    } else {
      pack.cells[i].balanceEnabled = false;
    }
  }

  bq76952SetBalancing(balanceMask);
}