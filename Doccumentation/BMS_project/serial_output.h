/*
  serial_output.h

  This header file declares the functions used to print BMS information
  to the Arduino Serial Monitor.

  These functions are defined in serial_output.cpp.

  Other files, such as main.ino, can include this header when they need
  to display battery voltage, temperature, fault, or system status data.
*/

/*
  Prints each individual cell voltage to the Serial Monitor.

  The voltage values come from the shared pack data structure.
*/
void printCellVoltages();

/*
  Prints the total battery pack voltage to the Serial Monitor.

  The pack voltage is displayed in millivolts.
*/
void printPackVoltage();

/*
  Prints the temperature readings for the battery cells.

  The temperature values are displayed in degrees Celsius.
*/
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