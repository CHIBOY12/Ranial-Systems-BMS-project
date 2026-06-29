#include "bms_fets.h"
#include "bms_data.h"
#include "bq76952_driver.h"

void bmsUpdateFets() {

    // If any protection fault is active,
    // immediately disable both charge and discharge FETs.
    if (pack.faultActive) {
        bq76952SetFETs(false, false);
    }
    else {
        // Otherwise, enable or disable each FET
        // according to the protection logic.
        bq76952SetFETs(pack.chargeAllowed,
                       pack.dischargeAllowed);
    }
}