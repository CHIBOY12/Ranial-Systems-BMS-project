#include "fault_manager.h"
#include "bms_data.h"
#include "bms_config.h"
#include "bq76952_driver.h"
#include "bq76952_registers.h"

BMSFaults faults;

void clearFaults() {
  faults.cellOvervoltage = false;
  faults.cellUndervoltage = false;
  faults.packOvervoltage = false;
  faults.packUndervoltage = false;
  faults.overtemperature = false;
  faults.overCurrent = false;
  faults.shortCircuit = false;
}

bool hasFault() {
  return faults.cellOvervoltage ||
         faults.cellUndervoltage ||
         faults.packOvervoltage ||
         faults.packUndervoltage ||
         faults.overtemperature ||
         faults.overCurrent ||
         faults.shortCircuit;
}

void updateFaults() {
  clearFaults();

  // Read the BQ76952 hardware protection state.
  uint16_t protectionStatus = bq76952ReadProtectionStatus();

  // Any OCC/OCD1/OCD2 hardware fault is reported as an overcurrent fault.
  if ((protectionStatus &
       (BQ76952_FAULT_OCC | BQ76952_FAULT_OCD1 | BQ76952_FAULT_OCD2)) != 0) {
    faults.overCurrent = true;
  }

  // Short Circuit in Discharge hardware fault.
  if ((protectionStatus & BQ76952_FAULT_SCD) != 0) {
    faults.shortCircuit = true;
  }

  // Evaluate ESP32-side software protection flags for each monitored cell.
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
