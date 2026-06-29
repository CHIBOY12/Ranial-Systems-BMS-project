#include "fault_manager.h"
#include "bms_data.h"

BMSFaults faults;

void clearFaults() {
  faults.cellOvervoltage = false;
  faults.cellUndervoltage = false;
  faults.packOvervoltage = false;
  faults.packUndervoltage = false;
  faults.overtemperature = false;
}

bool hasFault() {
  return faults.cellOvervoltage ||
         faults.cellUndervoltage ||
         faults.packOvervoltage ||
         faults.packUndervoltage ||
         faults.overtemperature;
}

void updateFaults() {
  clearFaults();

  for (int i = 0; i < NUM_CELLS; i++) {
    if (pack.cells[i].overVoltage) {
      faults.cellOvervoltage = true;
    }

    if (pack.cells[i].underVoltage) {
      faults.cellUndervoltage = true;
    }

    if (pack.cells[i].overTemp) {
      faults.overtemperature = true;
    }
  }

  pack.faultActive = hasFault();
}