#include "bms_fets.h"
#include "bms_data.h"
#include "bq76952_driver.h"

void bmsUpdateFets() {
  if (pack.faultActive) {
    bq76952SetFETs(false, false);
  } else {
    bq76952SetFETs(pack.chargeAllowed, pack.dischargeAllowed);
  }
}