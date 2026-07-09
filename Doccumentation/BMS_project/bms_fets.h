#ifndef BMS_FETS_H
#define BMS_FETS_H

//------------------------------------------------------------
// FET Control Function
//------------------------------------------------------------
// Updates the charge and discharge FET states.
//
// This function checks the current battery pack status,
// including protection faults and charge/discharge permissions,
// then sends the appropriate command to the BQ76952 to enable
// or disable the charge and discharge MOSFETs.
//------------------------------------------------------------


void bmsUpdateFets();

#endif