#include "config.h"
#include "bq76952_driver.h"
#include "battery_monitor.h"
#include "temperature_monitor.h"
#include "protection.h"
#include "fault_manager.h"
#include "serial_output.h"

void setup() {
  Serial.begin(115200);

  BQ76952_begin();
  clearFaults();
}

void loop() {
  readAllCellVoltages();
  readTemperatures();

  updateFaults();

  printSystemStatus();

  delay(1000);
}