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
  // Read voltage, current, and temperature data from the BQ76952.
  bq76952ReadCellVoltages(cellVoltage_mV);
  bq76952ReadPackVoltage(pack.packVoltage_mV);
  bq76952ReadCurrent(pack.current_A);
  bq76952ReadTemperatures(cellTemp_C);

  /*
    Initialize the minimum and maximum cell voltage values
    using Cell 1 as the starting reference.
  */
  pack.minCellVoltage_mV = cellVoltage_mV[0];
  pack.maxCellVoltage_mV = cellVoltage_mV[0];

  /*
    Copy the latest cell voltage readings into the main pack structure.

    This loop also finds the lowest and highest cell voltage in the pack.
  */
  for (int i = 0; i < NUM_CELLS; i++) {
    // Store the latest voltage measurement for this cell.
    pack.cells[i].voltage_mV = cellVoltage_mV[i];

    // Check for the lowest cell voltage.
    if (cellVoltage_mV[i] < pack.minCellVoltage_mV) {
      pack.minCellVoltage_mV = cellVoltage_mV[i];
    }

    // Check for the highest cell voltage.
    if (cellVoltage_mV[i] > pack.maxCellVoltage_mV) {
      pack.maxCellVoltage_mV = cellVoltage_mV[i];
    }
  }

  /*
    Assign physical temperature sensor readings to each battery cell.

    This is separate from the voltage loop because the temperature array
    includes more than just cell temperatures.

    cellTemp_C[0] is the internal BQ76952 temperature, so it should not
    automatically be used as Cell 1 temperature.
  */
  pack.cells[0].temperature_C = cellTemp_C[1];  // Cell 1 temperature from TS1
  pack.cells[1].temperature_C = cellTemp_C[2];  // Cell 2 temperature from TS2
  pack.cells[2].temperature_C = cellTemp_C[3];  // Cell 3 temperature from TS3
  pack.cells[3].temperature_C = cellTemp_C[4];  // Cell 4 temperature from HDQ
}