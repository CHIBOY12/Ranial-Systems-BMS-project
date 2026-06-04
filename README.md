# Ranial-Systems-BMS-project
Battery Management System using BQ76952 and MCU communication.
## 1. Device Description

### 1.1 Device Requirements

This project is a **Battery Management System (BMS)** designed to monitor and protect a rechargeable battery pack. A battery pack is made up of multiple battery cells connected in series, and each cell must stay within a safe voltage, current, and temperature range. If any cell goes too high, too low, gets too hot, or the pack draws too much current, the battery can become damaged or unsafe. The purpose of this device is to detect those conditions early and respond before they become serious problems.

The system uses the **BQ76952 battery monitor IC** to measure important battery information such as individual cell voltages, pack current, and temperature. The BQ76952 can support battery packs with **3 to 16 cells in series**, making it useful for medium-sized battery systems. The battery current is measured using a **shunt resistor** placed in the negative path of the battery pack. As current flows through the shunt resistor, a small voltage is created across it. The BQ76952 reads this small voltage and uses it to calculate the current flowing into or out of the battery.

The BMS communicates with a microcontroller using **I2C communication**. I2C is a simple communication method that lets the microcontroller request data from the BQ76952 and send configuration commands to it. Through I2C, the microcontroller can read cell voltages, current measurements, temperature readings, protection flags, and device status information.

This device also includes several important protection features. It can detect unsafe conditions such as:

- Overvoltage, when a cell voltage becomes too high
- Undervoltage, when a cell voltage becomes too low
- Overcurrent, when too much current flows through the battery
- Short circuit conditions
- Overtemperature or undertemperature conditions
- Internal diagnostic faults

Some safety responses are handled directly by the BQ76952 because they are time-critical. For example, short circuit and overcurrent protection need to happen very quickly, so the battery monitor IC can react without waiting for the microcontroller. Other functions, such as reading values, displaying information, logging data, or adjusting safety limits, can be handled by firmware on the microcontroller.

The system is also designed to measure voltage accurately with a small margin of error. Since battery safety depends on knowing the true voltage of each cell, the firmware should include voltage thresholds with tolerance margins. For example, instead of only checking whether a cell is exactly above or below a limit, the code should compare the measured voltage against safe upper and lower boundaries. This helps prevent false readings from noise or small measurement errors.

Another feature of the BMS is **cell balancing**. Over time, cells in a battery pack may not stay at the exact same voltage. Some cells may charge slightly faster or discharge slightly slower than others. Cell balancing helps reduce these differences so that the battery pack stays healthier and performs more consistently.

Overall, this project combines hardware monitoring and firmware control to create a safer and smarter battery pack. The BQ76952 handles accurate measurement and fast protection, while the microcontroller manages communication, decision-making, and user-level control. The final goal is to build a system that can reliably monitor battery health, detect dangerous conditions, and protect the battery pack during charging and discharging.

### Simple Summary

In simple terms, this project acts like a safety guard for a battery pack. It constantly checks the battery cells, current, and temperature. If something unsafe happens, such as a cell voltage getting too high or too much current being drawn, the system can detect it and help shut the battery down before damage occurs.