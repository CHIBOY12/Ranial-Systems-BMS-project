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
  bq76952ReadCellVoltages(cellVoltage_mV);        // Read the voltage of every battery cell from the BQ76952.
  bq76952ReadPackVoltage(pack.packVoltage_mV);    // Read the total battery pack voltage.
  bq76952ReadCurrent(pack.current_A);             // Read the battery pack current.
  bq76952ReadTemperatures(cellTemp_C);            // Read all temperature sensor values.


    // Initialize the minimum and maximum cell voltages
    // using the first cell's voltage.
  pack.minCellVoltage_mV = cellVoltage_mV[0];
  pack.maxCellVoltage_mV = cellVoltage_mV[0];

  for (int i = 0; i < NUM_CELLS; i++) {           // Loop through every battery cell.

    // Store the latest voltage measurement
    // into the battery pack structure.
    pack.cells[i].voltage_mV = cellVoltage_mV[i];

    // Store the latest temperature measurement
    // into the battery pack structure.
    pack.cells[i].temperature_C = cellTemp_C[i];

    if (cellVoltage_mV[i] < pack.minCellVoltage_mV) {  // Check if this cell has the lowest voltage.

      pack.minCellVoltage_mV = cellVoltage_mV[i];      // Update the minimum cell voltage.
    }

    if (cellVoltage_mV[i] > pack.maxCellVoltage_mV) {  // Check if this cell has the highest voltage.
      pack.maxCellVoltage_mV = cellVoltage_mV[i];      // Update the maximum cell voltage.
    }
  }
}