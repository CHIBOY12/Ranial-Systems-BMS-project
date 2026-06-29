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
void bq76952SendSubcommand(uint16_t subcommand) {
    // Sends a 2 byte subcommand to the BQ76952 command register 0x3E.
    // Low byte is sent first, then high byte.
    Wire.beginTransmission(BQ76952_I2C_ADDR);
    Wire.write(0x3E);
    Wire.write(subcommand & 0xFF);
    Wire.write((subcommand >> 8) & 0xFF);
    Wire.endTransmission();
}
uint16_t bq76952ReadProtectionStatus() {
    // Reads the BQ76952 safety status register.
    // The returned value contains protection fault flags.
    return bq76952ReadWord(BQ76952_SAFETY_STATUS_A);
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

    // If both charge and discharge are allowed,
    // release the BQ76952 FET block and allow all FETs to turn on.
    if (chargeEnable && dischargeEnable) {
        bq76952SendSubcommand(0x0096);   // ALL_FETS_ON()
    }

    // If both charge and discharge should be disabled,
    // turn off all BQ76952 FETs.
    else if (!chargeEnable && !dischargeEnable) {
        bq76952SendSubcommand(0x0095);   // ALL_FETS_OFF()
    }

    // If only charging is disabled,
    // turn off the charge and precharge FETs.
    else if (!chargeEnable && dischargeEnable) {
        bq76952SendSubcommand(0x0094);   // CHG_PCHG_OFF()
    }

    // If only discharging is disabled,
    // turn off the discharge and predischarge FETs.
    else if (chargeEnable && !dischargeEnable) {
        bq76952SendSubcommand(0x0093);   // DSG_PDSG_OFF()
    }
}

void bq76952SetBalancing(uint16_t balanceMask) {
  // Later: write to BQ76952 cell balancing control.
}