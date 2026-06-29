#include "bms_measurements.h"
#include "bms_protection.h"
#include "bms_balancing.h"
#include "bms_fets.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  bmsReadMeasurements();
  bmsUpdateProtection();
  bmsUpdateBalancing();
  bmsUpdateFets();

  delay(1000);
}