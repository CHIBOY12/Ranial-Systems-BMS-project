void bmsUpdateFets() {
  if (pack.faultActive) {
    bq76952SetFETs(false, false);
  } else {
    bq76952SetFETs(pack.chargeAllowed, pack.dischargeAllowed);
  }
}