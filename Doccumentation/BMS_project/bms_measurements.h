#ifndef BMS_MEASUREMENTS_H
#define BMS_MEASUREMENTS_H


//------------------------------------------------------------
// bmsReadMeasurements()
//------------------------------------------------------------
// Reads all battery measurements from the BQ76952.
//
// This function updates:
// • Cell voltages
// • Pack voltage
// • Pack current
// • Cell temperatures
// • Minimum cell voltage
// • Maximum cell voltage
//
// The updated values are stored in the global PackData
// structure and used by the protection, balancing,
// FET control, and serial output modules.
//------------------------------------------------------------

void bmsReadMeasurements();

#endif