#include "bms_measurements.h"
#include "bms_config.h"
#include "bms_data.h"
#include "battery_monitor.h"
#include "temperature_monitor.h"
#include "bq76952_driver.h"

void bmsReadMeasurements() {
  bq76952ReadCellVoltages(cellVoltage_mV);
  bq76952ReadPackVoltage(pack.packVoltage_mV);
  bq76952ReadCurrent(pack.current_A);
  bq76952ReadTemperatures(cellTemp_C);

  pack.minCellVoltage_mV = cellVoltage_mV[0];
  pack.maxCellVoltage_mV = cellVoltage_mV[0];

  for (int i = 0; i < NUM_CELLS; i++) {
    pack.cells[i].voltage_mV = cellVoltage_mV[i];
    pack.cells[i].temperature_C = cellTemp_C[i];

    if (cellVoltage_mV[i] < pack.minCellVoltage_mV) {
      pack.minCellVoltage_mV = cellVoltage_mV[i];
    }

    if (cellVoltage_mV[i] > pack.maxCellVoltage_mV) {
      pack.maxCellVoltage_mV = cellVoltage_mV[i];
    }
  }
}