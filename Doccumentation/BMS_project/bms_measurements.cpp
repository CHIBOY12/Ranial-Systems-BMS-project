/*
  bms_measurements.cpp

  This file is responsible for reading all live measurement data
  from the BQ76952 battery monitor and storing that data inside
  the shared pack data structure.
*/

#include "bms_measurements.h"     // Function declaration for bmsReadMeasurements()
#include "bms_config.h"           // Gives access to NUM_CELLS and project settings
#include "bms_data.h"             // Gives access to the global pack data structure
#include "battery_monitor.h"      // Gives access to cellVoltage_mV array
#include "temperature_monitor.h"  // Gives access to cellTemp_C array
#include "bq76952_driver.h"       // Gives access to BQ76952 read functions

/*
  bmsReadMeasurements()

  Reads the latest battery measurements from the BQ76952
  and stores them in the global pack structure.

  This function should be called repeatedly in the main loop.
*/
void bmsReadMeasurements() {

  /*
    Read individual cell voltages from the BQ76952.

    The values are stored in the cellVoltage_mV array.
    Example:
    cellVoltage_mV[0] = Cell 1 voltage
    cellVoltage_mV[1] = Cell 2 voltage
    cellVoltage_mV[2] = Cell 3 voltage
    cellVoltage_mV[3] = Cell 4 voltage
  */
  bq76952ReadCellVoltages(cellVoltage_mV);

  /*
    Read total pack voltage from the BQ76952.

    The value is stored directly into pack.packVoltage_mV.
  */
  bq76952ReadPackVoltage(pack.packVoltage_mV);

  /*
    Read pack current from the BQ76952.

    The value is stored directly into pack.current_A.
    Positive or negative current direction depends on the shunt wiring
    and BQ76952 configuration.
  */
  bq76952ReadCurrent(pack.current_A);

  /*
    Read temperature values from the BQ76952.

    The values are stored in the cellTemp_C array.
  */
  bq76952ReadTemperatures(cellTemp_C);

  /*
    Start the minimum and maximum voltage comparison using Cell 1.

    This gives the loop a valid starting point instead of starting
    from zero, which could give a false minimum value.
  */
  pack.minCellVoltage_mV = cellVoltage_mV[0];
  pack.maxCellVoltage_mV = cellVoltage_mV[0];

  /*
    Copy each cell's voltage and temperature into the main pack structure.

    This loop also checks which cell has the lowest voltage
    and which cell has the highest voltage.
  */
  for (int i = 0; i < NUM_CELLS; i++) {

    /*
      Store this cell's voltage into the pack data structure.
    */
    pack.cells[i].voltage_mV = cellVoltage_mV[i];

    /*
      Store this cell's temperature into the pack data structure.
    */
    pack.cells[i].temperature_C = cellTemp_C[i];

    /*
      Check if this cell is the new lowest-voltage cell.
    */
    if (cellVoltage_mV[i] < pack.minCellVoltage_mV) {
      pack.minCellVoltage_mV = cellVoltage_mV[i];
    }

    /*
      Check if this cell is the new highest-voltage cell.
    */
    if (cellVoltage_mV[i] > pack.maxCellVoltage_mV) {
      pack.maxCellVoltage_mV = cellVoltage_mV[i];
    }
  }
}