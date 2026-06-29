#include <Wire.h>
#include "bq76952_driver.h"
#include "bq76952_registers.h"

int16_t bq76952ReadWord(uint8_t command) {
  Wire.beginTransmission(BQ76952_I2C_ADDR);
  Wire.write(command);
  Wire.endTransmission(false);

  Wire.requestFrom(BQ76952_I2C_ADDR, 2);

  if (Wire.available() < 2) {
    return 0;
  }

  uint8_t lowByte = Wire.read();
  uint8_t highByte = Wire.read();

  return (int16_t)((highByte << 8) | lowByte);
}

void bq76952ReadCellVoltages(int cellVoltage_mV[]) {
  cellVoltage_mV[0] = bq76952ReadWord(BQ76952_CELL1_VOLTAGE);
  cellVoltage_mV[1] = bq76952ReadWord(BQ76952_CELL2_VOLTAGE);
  cellVoltage_mV[2] = bq76952ReadWord(BQ76952_CELL3_VOLTAGE);
  cellVoltage_mV[3] = bq76952ReadWord(BQ76952_CELL4_VOLTAGE);
}

void bq76952ReadPackVoltage(int &packVoltage_mV) {
  packVoltage_mV = bq76952ReadWord(BQ76952_PACK_VOLTAGE);
}

void bq76952ReadCurrent(float &current_A) {
  int16_t currentRaw = bq76952ReadWord(BQ76952_CC2_CURRENT);

  // Assumes USER_AMPS is configured as 1 mA/count.
  current_A = currentRaw / 1000.0;
}

void bq76952ReadTemperatures(int cellTemp_C[]) {
  int16_t ts1_raw = bq76952ReadWord(BQ76952_TS1_TEMP);
  int16_t ts2_raw = bq76952ReadWord(BQ76952_TS2_TEMP);
  int16_t ts3_raw = bq76952ReadWord(BQ76952_TS3_TEMP);

  cellTemp_C[0] = (ts1_raw / 10.0) - 273.15;
  cellTemp_C[1] = (ts2_raw / 10.0) - 273.15;
  cellTemp_C[2] = (ts3_raw / 10.0) - 273.15;
  cellTemp_C[3] = cellTemp_C[0];
}

void bq76952SetFETs(bool chargeEnable, bool dischargeEnable) {
  // Later: write to BQ76952 FET control subcommand/register.
}

void bq76952SetBalancing(uint16_t balanceMask) {
  // Later: write to BQ76952 cell balancing control.
}