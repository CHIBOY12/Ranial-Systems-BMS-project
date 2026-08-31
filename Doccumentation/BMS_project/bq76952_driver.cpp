#include <Wire.h>
#include "bq76952_driver.h"
#include "bq76952_registers.h"

static uint8_t bq76952Checksum(uint8_t addressLow,
                               uint8_t addressHigh,
                               uint8_t value) {
  uint16_t sum = addressLow + addressHigh + value;
  return (uint8_t)(~sum);
}

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
  // BQ76952 subcommands are written low byte first at 0x3E/0x3F.
  Wire.beginTransmission(BQ76952_I2C_ADDR);
  Wire.write(BQ76952_DM_COMMAND);
  Wire.write(subcommand & 0xFF);
  Wire.write((subcommand >> 8) & 0xFF);
  Wire.endTransmission();
}

bool bq76952WriteDataMemory(uint16_t address, uint8_t value) {
  uint8_t addressLow = (uint8_t)(address & 0xFF);
  uint8_t addressHigh = (uint8_t)((address >> 8) & 0xFF);

  // Write Data Memory address (0x3E/0x3F) followed by one byte at 0x40.
  Wire.beginTransmission(BQ76952_I2C_ADDR);
  Wire.write(BQ76952_DM_COMMAND);
  Wire.write(addressLow);
  Wire.write(addressHigh);
  Wire.write(value);

  uint8_t error = Wire.endTransmission();
  if (error != 0) {
    Serial.print("BQ76952 Data Memory write failed at 0x");
    Serial.println(address, HEX);
    return false;
  }

  delay(2);

  // For one data byte, TI's Data Memory length is 1 + 4 = 5 bytes.
  uint8_t checksum = bq76952Checksum(addressLow, addressHigh, value);
  uint8_t length = 0x05;

  // Checksum and length must be written together.
  Wire.beginTransmission(BQ76952_I2C_ADDR);
  Wire.write(BQ76952_DM_CHECKSUM);
  Wire.write(checksum);
  Wire.write(length);

  error = Wire.endTransmission();
  if (error != 0) {
    Serial.print("BQ76952 checksum/length write failed at 0x");
    Serial.println(address, HEX);
    return false;
  }

  delay(2);
  return true;
}

bool bq76952WaitForConfigUpdate() {
  const unsigned long timeoutMs = 1000;
  unsigned long startTime = millis();

  while ((millis() - startTime) < timeoutMs) {
    uint16_t batteryStatus =
        (uint16_t)bq76952ReadWord(BQ76952_BATTERY_STATUS);

    if ((batteryStatus & BQ76952_CFGUPDATE_BIT) != 0) {
      return true;
    }

    delay(10);
  }

  return false;
}

bool bq76952ConfigureThermistors() {
  Serial.println("Configuring BQ76952 thermistor inputs...");

  bool ok = true;

  // Configure TS1, TS2, and TS3 as external thermistor inputs.
  // These inputs are used for temperature measurement in the BMS.
  ok &= bq76952WriteDataMemory(BQ76952_TS1_CONFIG,
                               BQ76952_THERMISTOR_CONFIG);
  ok &= bq76952WriteDataMemory(BQ76952_TS2_CONFIG,
                               BQ76952_THERMISTOR_CONFIG);
  ok &= bq76952WriteDataMemory(BQ76952_TS3_CONFIG,
                               BQ76952_THERMISTOR_CONFIG);

  if (ok) {
    Serial.println("Thermistor configuration complete.");
  } else {
    Serial.println("Thermistor configuration failed.");
  }

  return ok;
}


bool bq76952ConfigureCurrentProtection() {
  Serial.println("Configuring BQ76952 current protections...");

  bool ok = true;

  // Configure overcurrent in charge protection.
  ok &= bq76952WriteDataMemory(BQ76952_OCC_THRESHOLD,
                               BQ76952_OCC_THRESHOLD_VALUE);
  ok &= bq76952WriteDataMemory(BQ76952_OCC_DELAY,
                               BQ76952_OCC_DELAY_VALUE);

  // Configure the two hardware overcurrent in discharge tiers.
  ok &= bq76952WriteDataMemory(BQ76952_OCD1_THRESHOLD,
                               BQ76952_OCD1_THRESHOLD_VALUE);
  ok &= bq76952WriteDataMemory(BQ76952_OCD1_DELAY,
                               BQ76952_OCD1_DELAY_VALUE);
  ok &= bq76952WriteDataMemory(BQ76952_OCD2_THRESHOLD,
                               BQ76952_OCD2_THRESHOLD_VALUE);
  ok &= bq76952WriteDataMemory(BQ76952_OCD2_DELAY,
                               BQ76952_OCD2_DELAY_VALUE);

  // Configure short-circuit-in-discharge protection.
  ok &= bq76952WriteDataMemory(BQ76952_SCD_THRESHOLD,
                               BQ76952_SCD_THRESHOLD_VALUE);
  ok &= bq76952WriteDataMemory(BQ76952_SCD_DELAY,
                               BQ76952_SCD_DELAY_VALUE);

  // Enable the current/short-circuit protections and retain COV hardware protection.
  ok &= bq76952WriteDataMemory(BQ76952_ENABLED_PROTECTIONS_A,
                               BQ76952_ENABLED_PROTECTIONS_A_VALUE);

  // Configure fast autonomous FET response to the enabled protection faults.
  ok &= bq76952WriteDataMemory(BQ76952_CHG_FET_PROTECTIONS_A,
                               BQ76952_CHG_FET_PROTECTIONS_A_VALUE);
  ok &= bq76952WriteDataMemory(BQ76952_DSG_FET_PROTECTIONS_A,
                               BQ76952_DSG_FET_PROTECTIONS_A_VALUE);

  if (ok) {
    Serial.println("Current protection configuration complete.");
  } else {
    Serial.println("Current protection configuration failed.");
  }

  return ok;
}

bool bq76952Initialize() {
  Serial.println("Initializing BQ76952...");

  // Allow the device time to be ready after startup/reset.
  delay(300);

  bq76952SendSubcommand(BQ76952_ENTER_CFG_UPDATE);

  if (!bq76952WaitForConfigUpdate()) {
    Serial.println("ERROR: BQ76952 did not enter CONFIG_UPDATE mode.");
    return false;
  }

  if (!bq76952ConfigureThermistors()) {
    bq76952SendSubcommand(BQ76952_EXIT_CFG_UPDATE);
    delay(20);
    return false;
  }

  if (!bq76952ConfigureCurrentProtection()) {
    bq76952SendSubcommand(BQ76952_EXIT_CFG_UPDATE);
    delay(20);
    return false;
  }

  bq76952SendSubcommand(BQ76952_EXIT_CFG_UPDATE);
  delay(20);

  Serial.println("BQ76952 initialization complete.");
  return true;
}

uint16_t bq76952ReadProtectionStatus() {
  // Safety Status A contains SCD, OCD2, OCD1, OCC, COV and CUV flags.
  return (uint16_t)bq76952ReadWord(BQ76952_SAFETY_STATUS_A);
}

void bq76952ReadCellVoltages(int cellVoltage_mV[]) {
  cellVoltage_mV[0] = bq76952ReadWord(BQ76952_CELL1_VOLTAGE);
  cellVoltage_mV[1] = bq76952ReadWord(BQ76952_CELL2_VOLTAGE);
  cellVoltage_mV[2] = bq76952ReadWord(BQ76952_CELL3_VOLTAGE);
  cellVoltage_mV[3] = bq76952ReadWord(BQ76952_CELL4_VOLTAGE);
}

/*
  bq76952ReadPackVoltage()

  Purpose:
  Reads the total battery stack voltage from the BQ76952.

  Important:
  This uses STACK_VOLTAGE instead of PACK_VOLTAGE.

  STACK_VOLTAGE represents the voltage across the cell stack.
  PACK_VOLTAGE represents the voltage at the PACK pin, which may be near 0
  if the PACK output path is not connected or the FET path is off.
*/
void bq76952ReadPackVoltage(int &packVoltage_mV) {
  packVoltage_mV = bq76952ReadWord(BQ76952_STACK_VOLTAGE);
}

void bq76952ReadCurrent(float &current_A) {
  int16_t currentRaw = bq76952ReadWord(BQ76952_CC2_CURRENT);

  // Assumes USER AMPS is configured as 1 mA/count.
  current_A = currentRaw / 1000.0;
}

/*
  bq76952ReadTemperatures()

  Purpose:
  Reads all selected temperature measurements from the BQ76952.

  The BQ76952 temperature commands return values in units of 0.1 Kelvin.
  This function converts those values into degrees Celsius before storing them.

  Temperature array mapping:
    cellTemp_C[0] = Internal BQ76952 temperature
    cellTemp_C[1] = TS1 temperature
    cellTemp_C[2] = TS2 temperature
    cellTemp_C[3] = TS3 temperature
    cellTemp_C[4] = HDQ temperature
    cellTemp_C[5] = DCHG temperature
    cellTemp_C[6] = DDSG temperature
*/
void bq76952ReadTemperatures(int cellTemp_C[]) {
  int16_t ts1_raw = bq76952ReadWord(BQ76952_TS1_TEMP);
  int16_t ts2_raw = bq76952ReadWord(BQ76952_TS2_TEMP);
  int16_t ts3_raw = bq76952ReadWord(BQ76952_TS3_TEMP);

  cellTemp_C[0] = (ts1_raw / 10.0) - 273.15;
  cellTemp_C[1] = (ts2_raw / 10.0) - 273.15;
  cellTemp_C[2] = (ts3_raw / 10.0) - 273.15;

  // Four temperature slots are maintained using three measured thermistor
  // channels, with the fourth slot mirroring the TS1 measurement.
  cellTemp_C[3] = cellTemp_C[0];
}

void bq76952SetFETs(bool chargeEnable, bool dischargeEnable) {
  if (chargeEnable && dischargeEnable) {
    bq76952SendSubcommand(BQ76952_ALL_FETS_ON);
  } else if (!chargeEnable && !dischargeEnable) {
    bq76952SendSubcommand(BQ76952_ALL_FETS_OFF);
  } else if (!chargeEnable && dischargeEnable) {
    bq76952SendSubcommand(BQ76952_CHG_PCHG_OFF);
  } else if (chargeEnable && !dischargeEnable) {
    bq76952SendSubcommand(BQ76952_DSG_PDSG_OFF);
  }
}

void bq76952SetBalancing(uint16_t balanceMask) {
  (void)balanceMask;
  // Cell balancing control is reserved for future implementation.
}
