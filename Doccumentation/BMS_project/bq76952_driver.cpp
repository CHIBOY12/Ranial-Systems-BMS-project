#include "bq76952_driver.h"

void bq76952ReadCellVoltages(int cellVoltage_mV[]) {
  for (int i = 0; i < NUM_CELLS; i++) {
    cellVoltage_mV[i] = 3700;
  }
}

void bq76952ReadPackVoltage(int &packVoltage_mV) {
  packVoltage_mV = 14800;
}

void bq76952ReadCurrent(float &current_A) {
  current_A = 0.0;
}

void bq76952ReadTemperatures(int cellTemp_C[]) {
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    cellTemp_C[i] = 25;
  }
}

void bq76952SetFETs(bool chargeEnable, bool dischargeEnable) {
  // Later: connect this to the real BQ76952 FET control code
}

void bq76952SetBalancing(uint16_t balanceMask) {
  // Later: connect this to the real BQ76952 cell balancing code
}