#include <Arduino.h>        // Gives access to Serial.print(), Serial.println(), and Arduino functions
#include "serial_output.h"  // Header file that declares the serial print functions
#include "bms_data.h"       // Gives access to the global pack data structure
#include "bms_config.h"     // Gives access to project constants such as NUM_CELLS
#include "fault_manager.h"  // Gives access to fault flags and the hasFault() function
#include "temperature_monitor.h" // Gives access to the raw temperature sensor array cellTemp_C[]
/*
  printCellVoltages()

  Purpose:
  Prints the voltage of each individual battery cell to the Serial Monitor.

  The voltage values come from:
  pack.cells[i].voltage_mV

  Each voltage is printed in millivolts.

  Example output:
  Cell 1: 3700 mV
  Cell 2: 3698 mV
*/
void printCellVoltages() {
  Serial.println("Cell Voltages:");

  // Loop through every cell in the battery pack
  for (int i = 0; i < NUM_CELLS; i++) {
    Serial.print("Cell ");
    Serial.print(i + 1);  // Add 1 so the display starts at Cell 1 instead of Cell 0
    Serial.print(": ");
    Serial.print(pack.cells[i].voltage_mV);  // Print the stored cell voltage
    Serial.println(" mV");
  }
}

/*
  printPackVoltage()

  Purpose:
  Prints the total battery pack voltage to the Serial Monitor.

  The pack voltage value comes from:
  pack.packVoltage_mV

  The value is printed in millivolts.
*/
void printPackVoltage() {
  Serial.print("Pack Voltage: ");
  Serial.print(pack.packVoltage_mV);  // Print total pack voltage
  Serial.println(" mV");
}

/*
  printTemperatures()

  Purpose:
  Prints the temperature associated with each battery cell.

  The temperature values come from:
  pack.cells[i].temperature_C

  Each temperature is printed in degrees Celsius.
*/
/*
  printTemperatures()

  Purpose:
  Prints all temperature readings to the Arduino Serial Monitor.

  This function prints two groups of temperature data:

  1. Cell temperatures stored in the pack structure.
     These are the values used by the protection logic.

  2. Raw BQ76952 temperature inputs.
     These come directly from cellTemp_C[] and include:
       - Internal BQ76952 temperature
       - TS1
       - TS2
       - TS3
       - HDQ
       - DCHG
       - DDSG

  Important:
  The pins HDQ, DCHG, and DDSG must be configured as thermistor inputs
  in BQStudio/Data Memory before they will show valid temperature readings.
*/
void printTemperatures() {
  Serial.println("Temperatures:");

  /*
    Print the temperature values stored inside the main pack structure.

    These values are copied from cellTemp_C[] inside bms_measurements.cpp.
    The protection code uses these values to check for overtemperature.
  */
  Serial.println("Cell Temperature Values Stored in Pack:");

  for (int i = 0; i < NUM_CELLS; i++) {
    Serial.print("Cell ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(pack.cells[i].temperature_C);
    Serial.println(" C");
  }

  /*
    Print all raw BQ76952 temperature command readings.

    Array mapping:
      cellTemp_C[0] = Internal BQ76952 temperature
      cellTemp_C[1] = TS1 temperature
      cellTemp_C[2] = TS2 temperature
      cellTemp_C[3] = TS3 temperature
      cellTemp_C[4] = HDQ temperature
      cellTemp_C[5] = DCHG temperature
      cellTemp_C[6] = DDSG temperature
  */
  Serial.println("BQ76952 Temperature Inputs:");

  Serial.print("Internal Temperature: ");
  Serial.print(cellTemp_C[0]);
  Serial.println(" C");

  Serial.print("TS1 Temperature: ");
  Serial.print(cellTemp_C[1]);
  Serial.println(" C");

  Serial.print("TS2 Temperature: ");
  Serial.print(cellTemp_C[2]);
  Serial.println(" C");

  Serial.print("TS3 Temperature: ");
  Serial.print(cellTemp_C[3]);
  Serial.println(" C");

  Serial.print("HDQ Temperature: ");
  Serial.print(cellTemp_C[4]);
  Serial.println(" C");

  Serial.print("DCHG Temperature: ");
  Serial.print(cellTemp_C[5]);
  Serial.println(" C");

  Serial.print("DDSG Temperature: ");
  Serial.print(cellTemp_C[6]);
  Serial.println(" C");
}
/*
  printFaults()

  Purpose:
  Prints the current fault status of the BMS.

  This function checks whether any fault is active using hasFault().
  If no faults are active, it prints "No faults active".

  If faults are active, it checks each fault flag and prints the fault name.
*/
void printFaults() {
  Serial.println("Fault Status:");

  // If no fault flags are active, print this message and leave the function
  if (!hasFault()) {
    Serial.println("No faults active");
    return;
  }

  // Print each active fault condition
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
}

/*
  printSystemStatus()

  Purpose:
  Prints a full BMS status report to the Serial Monitor.

  This function combines the smaller print functions into one complete report.

  It prints:
  - Individual cell voltages
  - Total pack voltage
  - Pack current
  - Cell temperatures
  - Fault status
  - Whether charging is allowed
  - Whether discharging is allowed
*/
void printSystemStatus() {
  Serial.println();
  Serial.println("----- BMS Status -----");

  // Print voltage information
  printCellVoltages();
  printPackVoltage();

  // Print current measurement
  Serial.print("Current: ");
  Serial.print(pack.current_A);
  Serial.println(" A");

  // Print temperature and fault information
  printTemperatures();
  printFaults();

  // Print whether the BMS currently allows charging
  Serial.print("Charge Allowed: ");
  Serial.println(pack.chargeAllowed ? "YES" : "NO");

  // Print whether the BMS currently allows discharging
  Serial.print("Discharge Allowed: ");
  Serial.println(pack.dischargeAllowed ? "YES" : "NO");

  Serial.println("----------------------");
}