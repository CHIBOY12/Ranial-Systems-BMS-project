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
#define BQ76952_CC2_CURRENT   0x3A

// Temperature direct command registers
#define BQ76952_INT_TEMP      0x68 // internal temp
#define BQ76952_TS1_TEMP      0x70 // ts1
#define BQ76952_TS2_TEMP      0x72 // ts2
#define BQ76952_TS3_TEMP      0x74 // ts3
#define BQ76952_HDQ_TEMP      0x76 // hdq
#define BQ76952_DCHG_TEMP     0x78 // dchg
#define BQ76952_DDSG_TEMP     0x7A // ddsg

// Safety alert/status registers
#define BQ76952_SAFETY_ALERT_A  0x02
#define BQ76952_SAFETY_STATUS_A 0x03
#define BQ76952_SAFETY_ALERT_B  0x04
#define BQ76952_SAFETY_STATUS_B 0x05
#define BQ76952_SAFETY_ALERT_C  0x06
#define BQ76952_SAFETY_STATUS_C 0x07

// FET status direct command register
#define BQ76952_FET_STATUS 0x7F

#endif