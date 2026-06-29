#ifndef BQ76952_DRIVER_H
#define BQ76952_DRIVER_H

#include <Arduino.h>
#include "bms_config.h"

void bq76952ReadCellVoltages(int cellVoltage_mV[]);
void bq76952ReadPackVoltage(int &packVoltage_mV);
void bq76952ReadCurrent(float &current_A);
void bq76952ReadTemperatures(int cellTemp_C[]);

void bq76952SetFETs(bool chargeEnable, bool dischargeEnable);
void bq76952SetBalancing(uint16_t balanceMask);

#endif