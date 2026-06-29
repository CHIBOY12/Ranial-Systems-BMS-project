#include <Arduino.h>
#include "bms_balancing.h"
#include "bms_config.h"
#include "bms_data.h"
#include "bq76952_driver.h"

void bmsUpdateBalancing() {
  uint16_t balanceMask = 0;

  for (int i = 0; i < NUM_CELLS; i++) {
    if (pack.cells[i].voltage_mV > pack.minCellVoltage_mV + 20) {
      balanceMask |= (1 << i);
    }
  }

  bq76952SetBalancing(balanceMask);
}