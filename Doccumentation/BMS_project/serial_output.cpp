#include <Arduino.h>
#include "serial_output.h"
#include "bms_data.h"
#include "bms_config.h"
#include "fault_manager.h"

void printCellVoltages() {
  Serial.println("Cell Voltages:");

  for (int i = 0; i < NUM_CELLS; i++) {
    Serial.print("Cell ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(pack.cells[i].voltage_mV);
    Serial.println(" mV");
  }
}

void printPackVoltage() {
  Serial.print("Pack Voltage: ");
  Serial.print(pack.packVoltage_mV);
  Serial.println(" mV");
}

void printCurrent() {
  Serial.print("Current: ");
  Serial.print(pack.current_A);
  Serial.println(" A");
}

void printTemperatures() {
  Serial.println("Temperatures:");

  for (int i = 0; i < NUM_CELLS; i++) {
    Serial.print("Cell ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(pack.cells[i].temperature_C);
    Serial.println(" C");
  }
}

void printFaults() {
  Serial.println("Fault Status:");

  if (!hasFault()) {
    Serial.println("No faults active");
    return;
  }

  if (faults.cellOvervoltage) {
    Serial.println("Cell overvoltage fault");
  }

  if (faults.cellUndervoltage) {
    Serial.println("Cell undervoltage fault");
  }

  if (faults.packOvervoltage) {
    Serial.println("Pack overvoltage fault");
  }

  if (faults.packUndervoltage) {
    Serial.println("Pack undervoltage fault");
  }

  if (faults.overtemperature) {
    Serial.println("Overtemperature fault");
  }

  if (faults.overCurrent) {
    Serial.println("Overcurrent fault");
  }

  if (faults.shortCircuit) {
    Serial.println("Short-circuit fault");
  }
}

void printSystemStatus() {
  Serial.println();
  Serial.println("----- BMS Status -----");

  printCellVoltages();
  printPackVoltage();
  printCurrent();
  printTemperatures();
  printFaults();

  Serial.print("Charge Allowed: ");
  Serial.println(pack.chargeAllowed ? "YES" : "NO");

  Serial.print("Discharge Allowed: ");
  Serial.println(pack.dischargeAllowed ? "YES" : "NO");

  Serial.println("----------------------");
}
