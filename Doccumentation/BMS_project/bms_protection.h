#ifndef BMS_PROTECTION_H
#define BMS_PROTECTION_H

//------------------------------------------------------------
// bmsUpdateProtection()
//------------------------------------------------------------
// Evaluates all battery protection conditions using the
// latest measurements stored in the PackData structure.
//
// Protection checks performed include:
// • Cell over voltage
// • Cell under voltage
// • Cell over temperature
// • Pack over current
// • Short circuit detection

void bmsUpdateProtection();

#endif