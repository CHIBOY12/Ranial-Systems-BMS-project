#ifndef BMS_DATA_H
#define BMS_DATA_H

#include "bms_config.h"

struct CellData {
  int voltage_mV;
  int temperature_C;
  bool overVoltage;
  bool underVoltage;
  bool overTemp;
};

struct PackData {
  CellData cells[NUM_CELLS];

  int packVoltage_mV;
  float current_A;

  int minCellVoltage_mV;
  int maxCellVoltage_mV;

  bool chargeAllowed;
  bool dischargeAllowed;
  bool faultActive;
};

extern PackData pack;

#endif