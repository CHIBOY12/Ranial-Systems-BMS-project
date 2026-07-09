#include <Wire.h> // Arduino I2C communication library
#include "bms_measurements.h"  // Reads battery measurements from the BQ76952
#include "bms_protection.h"    // Handles battery protection logic
#include "fault_manager.h"     // Manages system fault conditions
#include "bms_balancing.h"    // Controls cell balancing
#include "bms_fets.h"         // Controls charge and discharge FETs
#include "serial_output.h"    // Prints system information to the Serial Monitor

//------------------------------------------------------------
// Setup function
// Runs once when the ESP32 powers on or is reset.
//------------------------------------------------------------


void setup() {
  Serial.begin(115200);   // Start Serial communication for debugging
    Wire.begin();         // Initialize the ESP32 I2C bus

  clearFaults();          // Clear any existing BQ76952 fault flags
}

//------------------------------------------------------------
// Main loop
// Runs continuously while the ESP32 is powered.
//------------------------------------------------------------


void loop() {
  bmsReadMeasurements();   // Read voltages, temperatures, and current from the BQ76952
  bmsUpdateProtection();   // Check for unsafe operating conditions
  updateFaults();          // Update the system fault status
  bmsUpdateBalancing();    // Determine whether cell balancing should be enabled
  bmsUpdateFets();         // Enable or disable charge/discharge FETs
  printSystemStatus();     // Display all battery information on the Serial Monitor

  delay(1000);             // Wait 1 second before repeating the loop
}