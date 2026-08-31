#ifndef SERIAL_OUTPUT_H
#define SERIAL_OUTPUT_H

void printCellVoltages();

/*
  Prints the total battery pack voltage to the Serial Monitor.

  The pack voltage is displayed in millivolts.
*/
void printPackVoltage();
void printCurrent();
void printTemperatures();

/*
  Prints the active BMS fault conditions.

  If no faults are active, it prints that the system has no active faults.
*/
void printFaults();

/*
  Prints a full BMS status report.

  This function combines:
  - cell voltages
  - pack voltage
  - current
  - temperatures
  - faults
  - charge permission
  - discharge permission
*/
void printSystemStatus();

#endif
