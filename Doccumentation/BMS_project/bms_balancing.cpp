#include <Arduino.h>          // Arduino core library
#include "bms_balancing.h"    // Cell balancing function declarations
#include "bms_config.h"       // System configuration constants
#include "bms_data.h"         // Battery pack data structures
#include "bq76952_driver.h"   // BQ76952 driver functions


//------------------------------------------------------------
// Cell Balancing Function
// Determines which cells should be balanced and sends the
// balancing mask to the BQ76952.
//------------------------------------------------------------

void bmsUpdateBalancing() {

// Bitmask that tells the BQ76952 which cells should balance.
// Each bit represents one battery cell.

  uint16_t balanceMask = 0;
// Loop through every battery cell.
  for (int i = 0; i < NUM_CELLS; i++) {

     // If this cell is more than 20 mV above the lowest cell,
     // mark it for balancing.
    if (pack.cells[i].voltage_mV > pack.minCellVoltage_mV + 20) {

// Set the bit corresponding to this cell.
            // Example:
            // Cell 0 -> bit 0
            // Cell 1 -> bit 1
            // Cell 2 -> bit 2

      balanceMask |= (1 << i);
    }
  }

   // Send the completed balancing mask to the BQ76952.
   // The BQ76952 will enable balancing only for the selected cells.

  bq76952SetBalancing(balanceMask);
}