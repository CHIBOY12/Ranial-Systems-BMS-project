#ifndef BQ76952_REGISTERS_H
#define BQ76952_REGISTERS_H

// BQ76952 I2C address
#define BQ76952_I2C_ADDR 0x08

// Cell voltage direct command registers
#define BQ76952_CELL1_VOLTAGE 0x14
#define BQ76952_CELL2_VOLTAGE 0x16
#define BQ76952_CELL3_VOLTAGE 0x18
#define BQ76952_CELL4_VOLTAGE 0x1A

// Stack, PACK, and LD voltage direct command registers
#define BQ76952_STACK_VOLTAGE 0x34
#define BQ76952_PACK_VOLTAGE  0x36
#define BQ76952_LD_VOLTAGE    0x38

// Current direct command register
#define BQ76952_CC2_CURRENT 0x3A

// Battery status direct command register
#define BQ76952_BATTERY_STATUS 0x12
#define BQ76952_CFGUPDATE_BIT  0x0001

// Temperature direct command registers
#define BQ76952_INT_TEMP  0x68
#define BQ76952_TS1_TEMP  0x70
#define BQ76952_TS2_TEMP  0x72
#define BQ76952_TS3_TEMP  0x74
#define BQ76952_HDQ_TEMP  0x76
#define BQ76952_DCHG_TEMP 0x78
#define BQ76952_DDSG_TEMP 0x7A

// Safety alert/status registers
#define BQ76952_SAFETY_ALERT_A  0x02
#define BQ76952_SAFETY_STATUS_A 0x03
#define BQ76952_SAFETY_ALERT_B  0x04
#define BQ76952_SAFETY_STATUS_B 0x05
#define BQ76952_SAFETY_ALERT_C  0x06
#define BQ76952_SAFETY_STATUS_C 0x07

// Safety Status A bit masks
#define BQ76952_FAULT_SCD  (1U << 7)
#define BQ76952_FAULT_OCD2 (1U << 6)
#define BQ76952_FAULT_OCD1 (1U << 5)
#define BQ76952_FAULT_OCC  (1U << 4)
#define BQ76952_FAULT_COV  (1U << 3)
#define BQ76952_FAULT_CUV  (1U << 2)

// FET status direct command register
#define BQ76952_FET_STATUS 0x7F

// Subcommands
#define BQ76952_ENTER_CFG_UPDATE 0x0090
#define BQ76952_EXIT_CFG_UPDATE  0x0092
#define BQ76952_DSG_PDSG_OFF     0x0093
#define BQ76952_CHG_PCHG_OFF     0x0094
#define BQ76952_ALL_FETS_OFF     0x0095
#define BQ76952_ALL_FETS_ON      0x0096

// Data Memory communication registers
#define BQ76952_DM_COMMAND  0x3E
#define BQ76952_DM_BUFFER   0x40
#define BQ76952_DM_CHECKSUM 0x60
#define BQ76952_DM_LENGTH   0x61

// Multifunction-pin Data Memory addresses
#define BQ76952_TS1_CONFIG  0x92FD
#define BQ76952_TS2_CONFIG  0x92FE
#define BQ76952_TS3_CONFIG  0x92FF
#define BQ76952_HDQ_CONFIG  0x9300
#define BQ76952_DCHG_CONFIG 0x9301
#define BQ76952_DDSG_CONFIG 0x9302

// 18-kohm thermistor configuration for the TS1, TS2, and TS3 inputs.
#define BQ76952_THERMISTOR_CONFIG 0x0B

// Current and short-circuit protection Data Memory addresses.
// These registers define programmable OCC, OCD, and SCD protection settings.
#define BQ76952_ENABLED_PROTECTIONS_A 0x9261
#define BQ76952_CHG_FET_PROTECTIONS_A 0x9265
#define BQ76952_DSG_FET_PROTECTIONS_A 0x9269
#define BQ76952_OCC_THRESHOLD         0x9280
#define BQ76952_OCC_DELAY             0x9281
#define BQ76952_OCD1_THRESHOLD        0x9282
#define BQ76952_OCD1_DELAY            0x9283
#define BQ76952_OCD2_THRESHOLD        0x9284
#define BQ76952_OCD2_DELAY            0x9285
#define BQ76952_SCD_THRESHOLD         0x9286
#define BQ76952_SCD_DELAY             0x9287

// Current/short-circuit protection settings based on TI BQ76952 defaults.
// With the 1-mohm sense resistor on the BQ76952EVM, the thresholds correspond
// to approximately 4 A OCC, 8 A OCD1, 6 A OCD2, and 10 A SCD.
#define BQ76952_OCC_THRESHOLD_VALUE   0x02
#define BQ76952_OCC_DELAY_VALUE       0x04
#define BQ76952_OCD1_THRESHOLD_VALUE  0x04
#define BQ76952_OCD1_DELAY_VALUE      0x01
#define BQ76952_OCD2_THRESHOLD_VALUE  0x03
#define BQ76952_OCD2_DELAY_VALUE      0x07
#define BQ76952_SCD_THRESHOLD_VALUE   0x00
#define BQ76952_SCD_DELAY_VALUE       0x02

// Enable SCD, OCD2, OCD1, OCC, and COV.
#define BQ76952_ENABLED_PROTECTIONS_A_VALUE 0xF8

// Fast autonomous FET response masks recommended/defaulted by TI.
#define BQ76952_CHG_FET_PROTECTIONS_A_VALUE 0x98
#define BQ76952_DSG_FET_PROTECTIONS_A_VALUE 0xE4

#endif
