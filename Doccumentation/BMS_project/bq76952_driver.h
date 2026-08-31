#ifndef BQ76952_DRIVER_H
#define BQ76952_DRIVER_H

#include <Arduino.h>
#include "bms_config.h"

int16_t bq76952ReadWord(uint8_t command);

void bq76952ReadCellVoltages(int cellVoltage_mV[]);
void bq76952ReadPackVoltage(int &packVoltage_mV);
void bq76952ReadCurrent(float &current_A);
void bq76952ReadTemperatures(int cellTemp_C[]);

uint16_t bq76952ReadProtectionStatus();
void bq76952SendSubcommand(uint16_t subcommand);

bool bq76952WriteDataMemory(uint16_t address, uint8_t value);
bool bq76952WaitForConfigUpdate();
bool bq76952ConfigureThermistors();
bool bq76952ConfigureCurrentProtection();
bool bq76952Initialize();

void bq76952SetFETs(bool chargeEnable, bool dischargeEnable);
void bq76952SetBalancing(uint16_t balanceMask);

#endif
