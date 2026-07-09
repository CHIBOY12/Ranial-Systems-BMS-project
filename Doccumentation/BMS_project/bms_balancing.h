#ifndef BMS_BALANCING_H     // Prevent multiple inclusions of this header file
#define BMS_BALANCING_H 

// Updates the cell balancing status.
// This function determines which battery cells should be balanced
// and sends the balancing command to the BQ76952 battery monitor IC.

void bmsUpdateBalancing();

#endif