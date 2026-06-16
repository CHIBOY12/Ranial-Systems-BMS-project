#include "config.h"
#include "data_types.h"
#include "bq76952_driver.h"
#include "bms_measurements.h"
#include "bms_protection.h"
#include "bms_balancing.h"
#include "bms_fets.h"
#include "bms_storage.h"
#include "bms_comms.h"
#include "bms_debug.h"
#include "bms_state.h"

void setup() {
  bmsStorageInit();
  bmsCommsInit();
  bq76952Init();
  bmsFetsInit();
  bmsDebugInit();
}

void loop() {
  bmsReadMeasurements();
  bmsUpdateProtection();
  bmsUpdateBalancing();
  bmsUpdateFets();
  bmsHandleCommands();
  bmsPrintDebug();
}