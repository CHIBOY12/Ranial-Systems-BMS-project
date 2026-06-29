#include <Wire.h>
#include "bms_measurements.h"
#include "bms_protection.h"
#include "fault_manager.h"
#include "bms_balancing.h"
#include "bms_fets.h"
#include "serial_output.h"

void setup() {
  Serial.begin(115200);
    Wire.begin();

  clearFaults();
}

void loop() {
  bmsReadMeasurements();
  bmsUpdateProtection();
  updateFaults();
  bmsUpdateBalancing();
  bmsUpdateFets();
  printSystemStatus();

  delay(1000);
}