#include <Wire.h>              // Arduino I2C communication library
#include "bq76952_driver.h"    // Low level BQ76952 communication configuration
#include "bms_measurements.h"  // Reads battery measurements from the BQ76952
#include "bms_protection.h"    // Handles battery protection logic
#include "fault_manager.h"     // Manages system fault conditions
#include "bms_balancing.h"     // Controls cell balancing
#include "bms_fets.h"          // Controls charge and discharge FETs
#include "serial_output.h"     // Prints system information to the Serial Monitor

//------------------------------------------------------------
// Setup function
// Runs once when the ESP32 powers on or is reset.
//------------------------------------------------------------
void setup() {
  Serial.begin(115200);  // Start Serial communication for debugging
  Wire.begin();          // Initialize the ESP32 I2C bus

  // Configure BQ76952 settings that previously depended on external setup.
  if (!bq76952Initialize()) {
    Serial.println("WARNING: BQ76952 initialization failed.");
  }

  // Clear ESP32 side software fault flags before entering the main loop.
  clearFaults();
}

//------------------------------------------------------------
// Main loop
// Runs continuously while the ESP32 is powered.
//------------------------------------------------------------
void loop() {
  bmsReadMeasurements();  // Read voltages, temperatures, and current
  bmsUpdateProtection();  // Check software protection conditions
  updateFaults();         // Include BQ hardware faults in system fault status
  bmsUpdateBalancing();   // Determine whether cell balancing should be enabled
  bmsUpdateFets();        // Enable or disable charge/discharge FETs
  printSystemStatus();    // Display battery information and active faults

  delay(1000);            // Wait 1 second before repeating the loop
  
}