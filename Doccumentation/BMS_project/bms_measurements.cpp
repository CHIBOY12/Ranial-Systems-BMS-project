#include "bms_measurements.h"        // Measurement function declarations
#include "bms_config.h"              // System configuration constants
#include "bms_data.h"                // Global battery data structure
#include "battery_monitor.h"         // Cell voltage storage array
#include "temperature_monitor.h"     // Cell temperature storage array
#include "bq76952_driver.h"          // BQ76952 driver functions


//------------------------------------------------------------
// Battery Measurement Function
//------------------------------------------------------------
// Reads all battery measurements from the BQ76952 and updates
// the shared battery pack data structure.
//
// Measurements include:
// - Cell voltages
// - Pack voltage
// - Pack current
// - Cell temperatures
// - Minimum cell voltage
// - Maximum cell voltage
//------------------------------------------------------------

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