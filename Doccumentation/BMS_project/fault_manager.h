#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

struct BMSFaults {
  bool cellOvervoltage;
  bool cellUndervoltage;
  bool packOvervoltage;
  bool packUndervoltage;
  bool overtemperature;
  bool overCurrent;
  bool shortCircuit;
};

extern BMSFaults faults;

void clearFaults();
bool hasFault();
void updateFaults();

#endif