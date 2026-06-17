#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <Arduino.h>
#include "config.h"

struct CellData {
  int voltage_mV;
  int temperature_C;
  bool overVoltage;
  bool underVoltage;
  bool overTemp;
  bool balanceEnabled;
};

struct PackData {
  CellData cells[NUM_CELLS];

  long packVoltage_mV;
  float current_A;

  int minCellVoltage_mV;
  int maxCellVoltage_mV;
  int averageCellVoltage_mV;

  bool chargeAllowed;
  bool dischargeAllowed;
  bool faultActive;
};

extern PackData pack;

#endif