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

# Appendix: Requirements Specification

## 1. Software Requirements Specification

### 1.1 Overview

The software for this project shall control and monitor a Battery Management System using a microcontroller and the BQ76952 battery monitor IC. The software shall communicate with the BQ76952 using I2C, read battery measurements, check for unsafe operating conditions, and respond to faults. The software shall help protect the battery pack by monitoring cell voltage, pack current, temperature, and device status.

### 1.2 Users

The users of this software are students, engineers, and technicians who need to monitor the condition of a rechargeable battery pack. The user does not directly control the battery cells but can use the system to view battery status, detect faults, and verify that the battery pack is operating safely.

### 1.3 Definitions and Abbreviations

- **BMS**: Battery Management System  
- **MCU**: Microcontroller Unit  
- **IC**: Integrated Circuit  
- **I2C**: Inter-Integrated Circuit, a communication protocol used between the MCU and BQ76952  
- **ADC**: Analog-to-Digital Converter  
- **SOC**: State of Charge  
- **OV**: Overvoltage  
- **UV**: Undervoltage  
- **OCD**: Overcurrent in Discharge  
- **OCC**: Overcurrent in Charge  
- **SCD**: Short Circuit in Discharge  
- **Shunt Resistor**: A small resistor used to measure current by sensing voltage drop  

### 1.4 Functionality

### Software Requirements Specification

**SRS 01** – The software shall initialize I2C communication between the ESP32-C3 and the BQ76952 at system startup using SDA and SCL pins assigned in firmware.

**SRS 02** – The software shall verify BQ76952 communication during startup by reading a device status or identification register before entering the main monitoring loop.

**SRS 03** – The software shall read voltage measurements for all 16 series-connected battery cells from the BQ76952 at least once every 1 second.

**SRS 04** – The software shall store each cell voltage in millivolts in a 16-element array named `cellVoltage_mV[16]`.

**SRS 05** – The software shall compare each cell voltage against a minimum cell voltage threshold of 3000 mV and a maximum cell voltage threshold of 4200 mV for a 16S Li-ion battery pack.

**SRS 06** – The software shall identify an undervoltage fault if any cell voltage is less than or equal to 3000 mV for 3 consecutive readings.

**SRS 07** – The software shall identify an overvoltage fault if any cell voltage is greater than or equal to 4200 mV for 3 consecutive readings.

**SRS 08** – The software shall use a voltage tolerance margin of ±50 mV when displaying warning conditions to reduce false warnings caused by measurement noise.

**SRS 09** – The software shall read pack current from the BQ76952 using the SRP/SRN shunt measurement at least once every 1 second.

**SRS 10** – The software shall identify a discharge overcurrent fault if pack current exceeds the programmed discharge current limit for 2 consecutive readings.

**SRS 11** – The software shall read temperature measurements from thermistors connected to TS1, TS2, and TS3 at least once every 1 second.

**SRS 12** – The software shall identify an overtemperature fault if any measured temperature is greater than or equal to 60°C.

**SRS 13** – The software shall identify an undertemperature fault if any measured temperature is less than or equal to 0°C during charging.

**SRS 14** – The software shall read the BQ76952 protection status registers once every monitoring cycle to check for overvoltage, undervoltage, overcurrent, short circuit, and temperature faults.

**SRS 15** – The software shall turn on the fault LED and activate the buzzer when any critical fault is detected.

**SRS 16** – The software shall turn off the fault LED and buzzer only after the fault condition is cleared and the system has completed a normal status check.

**SRS 17** – The software shall print cell voltages, pack current, temperature values, and active fault states to the Serial Monitor at least once every 1 second.

**SRS 18** – The software shall send battery status data from the ESP32-C3 to a Wi-Fi dashboard at least once every 5 seconds when Wi-Fi is connected.

**SRS 19** – The software shall initialize all required BQ76952 configuration settings before normal monitoring begins, including cell count, protection thresholds, temperature inputs, and alert behavior.

**SRS 20** – The software shall use the BQ76952 ALERT signal as an ESP32-C3 GPIO input to detect when the BQ76952 reports a fault or important battery event.

**SRS 21** – The software shall prevent normal battery operation from being reported as “safe” while any critical BQ76952 protection fault is active.

**SRS 22** – The software shall support firmware-defined threshold constants for cell overvoltage, cell undervoltage, overcurrent, and temperature limits so values can be adjusted during testing.

**SRS 23** – The software should support cell balancing by identifying cells that are at least 50 mV higher than the lowest measured cell voltage.

**SRS 24** – The software should enable balancing only when the battery pack is charging and no critical fault is active.

## 2. Hardware Requirements Specification

### 2.1 Overview

The hardware for this project shall use the BQ76952 battery monitor IC to monitor and protect a multi-cell rechargeable battery pack. The hardware shall support voltage sensing, current sensing, temperature sensing, communication with a microcontroller, and battery protection features. The system shall be designed to detect unsafe battery conditions and protect the battery pack from damage.

### 2.2 Definitions and Abbreviations

- **BMS**: Battery Management System  
- **BQ76952**: Battery monitor and protection IC used in this project  
- **MCU**: Microcontroller Unit  
- **I2C**: Inter-Integrated Circuit communication protocol  
- **NFET**: N-channel Field Effect Transistor  
- **ADC**: Analog-to-Digital Converter  
- **Cell**: One individual battery unit inside a larger battery pack  
- **Series Connection**: Battery cells connected so their voltages add together  
- **Shunt Resistor**: A precision resistor used to measure current  
- **Thermistor**: A temperature-sensitive resistor used for temperature measurement  

### 2.3 Functionality

## Revised Hardware Requirements Specification

**HRS 01** – The hardware shall use the BQ76952 as the main battery monitoring and protection IC for a 16-series Li-ion battery pack.

**HRS 02** – The hardware shall support a 16S Li-ion battery pack with a nominal voltage of 59.2 V and a maximum fully charged voltage of 67.2 V.

**HRS 03** – The hardware shall provide 17 cell tap connections from the battery stack to the BQ76952, using VC0 through VC16.

**HRS 04** – The hardware shall connect each cell tap line to the BQ76952 through cell input RC filter components to reduce measurement noise.

**HRS 05** – The hardware shall include a current sense shunt resistor in the negative current path between the battery stack negative terminal and PACK-.

**HRS 06** – The hardware shall connect the two sides of the shunt resistor to the BQ76952 SRP and SRN pins for differential current sensing.

**HRS 07** – The hardware shall include 100 Ω series resistors on the SRP and SRN sense lines.

**HRS 08** – The hardware shall include a 100 nF differential filter capacitor between the SRP and SRN sense lines.

**HRS 09** – The hardware shall support current sensing during both battery charging and battery discharging through the same shunt resistor.

**HRS 10** – The hardware shall include three temperature sensing inputs connected to the BQ76952 TS1, TS2, and TS3 pins.

**HRS 11** – The hardware shall use one thermistor near the battery cell stack, one thermistor near the MOSFET protection area, and one thermistor for ambient or additional pack temperature monitoring.

**HRS 12** – The hardware shall connect the BQ76952 SDA and SCL pins to the ESP32-C3 I2C bus.

**HRS 13** – The hardware shall include pull-up resistors from SDA and SCL to the 3.3 V logic rail.

**HRS 14** – The hardware shall connect the BQ76952 ALERT pin to an ESP32-C3 GPIO input pin for fault interrupt detection.

**HRS 15** – The hardware shall include charge and discharge protection MOSFETs controlled by the BQ76952 CHG and DSG outputs.

**HRS 16** – The hardware shall include precharge and predischarge MOSFET control paths using the BQ76952 PCHG and PDSG outputs.

**HRS 17** – The hardware shall route the main high-current battery path through the protection MOSFETs before reaching the PACK+ and PACK- output terminals.

**HRS 18** – The hardware shall provide PACK+ and PACK- output connectors for connection to an external load or charger.

**HRS 19** – The hardware shall include a high-voltage buck converter that converts the 16S battery voltage range to a regulated 3.3 V output.

**HRS 20** – The 3.3 V rail shall power the ESP32-C3, I2C pull-up resistors, status LEDs, and low-voltage user-interface circuitry.

**HRS 21** – The hardware shall include a status LED connected to an ESP32-C3 GPIO pin.

**HRS 22** – The hardware shall include a fault LED connected to an ESP32-C3 GPIO pin.

**HRS 23** – The hardware shall include a fault buzzer connected to an ESP32-C3 GPIO or PWM-capable pin.

**HRS 24** – The hardware shall include a reset or wake button connected to the ESP32-C3 or BQ76952 wake/shutdown control circuit.

**HRS 25** – The hardware shall include cell balancing connections for all 16 cells through the BQ76952 VC0–VC16 cell monitoring network.

**HRS 26** – The hardware shall include test points for PACK+, PACK-, 3.3 V, GND, SDA, SCL, ALERT, SRP, and SRN.

**HRS 27** – The hardware shall include connectors for the 16S cell tap harness, PACK+/PACK- output, thermistors, and ESP32-C3 programming/debug access.

**HRS 28** – The hardware shall not connect the 16S battery pack directly to the ESP32-C3 without voltage regulation.

**HRS 29** – The hardware shall not bypass the shunt resistor in the main current path when current measurement is required.

**HRS 30** – The hardware shall not connect battery cell tap lines to the wrong BQ76952 VC pins, since incorrect VC order can damage the BQ76952 or produce unsafe voltage readings.


#  User Persona

### Persona: Marcus Reed

**Name:** Marcus Reed  
**Age:** 34  
**Gender:** Male  
**Education:** Bachelor’s Degree in Mechanical Engineering  
**Location:** Rochester, NY  
**Living Situation:** Lives with his wife and young daughter in a single-family home  
**Occupation:** Electric bike repair technician and small business owner  
**Technical Experience:** Comfortable with basic electrical systems, battery packs, multimeters, and repair tools, but not an expert in embedded software or battery monitoring ICs  
**Hobbies:** Riding electric bikes, repairing electronics, camping, and teaching his daughter how things work  
**Favorite Brands:** Bosch, Anker, Milwaukee, Samsung  
**Devices Used:** Electric bike, portable power station, laptop, smartphone, and digital multimeter  

### Background

Marcus owns a small electric bike repair shop. Many of his customers bring in battery packs that are not charging correctly, losing range too quickly, or shutting off during use. Since battery problems can be dangerous, Marcus needs a reliable way to monitor battery voltage, current, and temperature before deciding whether a battery pack is safe to use.

Marcus is not designing battery management hardware from scratch, but he understands why battery safety matters. He wants a device that can clearly show whether a battery pack is healthy or unsafe. He does not want to guess based only on how the battery “feels” or how long it lasts during a ride.

### Goals

Marcus wants to use the Battery Management System to:

- Monitor individual battery cell voltages
- Detect unsafe voltage, current, and temperature conditions
- Prevent battery damage during charging and discharging
- Identify weak or unbalanced cells
- Improve customer safety
- Reduce the risk of overheating, short circuits, or battery failure

### Frustrations

Marcus gets frustrated when battery systems do not clearly explain what is wrong. Some battery packs simply stop working without showing whether the issue is low voltage, overcurrent, overheating, or cell imbalance. He also dislikes systems that require too much technical setup before they can provide useful information.

His biggest frustration is that battery failures can become dangerous quickly. If a battery pack overheats or a cell voltage becomes too high or too low, the user may not notice until the damage has already happened.

### Needs

Marcus needs the device to be:

- Safe and reliable
- Easy to connect to a battery pack
- Accurate enough to detect small voltage changes
- Able to warn the user when a fault occurs
- Capable of monitoring multiple cells in series
- Useful for both testing and real battery operation

### How Marcus Would Use the Device

Marcus would connect the Battery Management System to a rechargeable battery pack before testing or repairing it. The system would monitor each cell voltage, the total pack current, and the battery temperature. If the BMS detects an unsafe condition, such as overvoltage, undervoltage, overcurrent, or overheating, it would alert Marcus or trigger protection behavior.

For Marcus, the most important feature is trust. He needs to know that the system is constantly checking the battery and will respond if something becomes unsafe. This helps him protect his customers, his equipment, and his repair shop.

### Design Takeaway

This persona shows that the BMS should not only be technically functional, but also understandable to someone who works with batteries in real situations. The device should provide clear fault information, accurate measurements, and dependable protection so users like Marcus can make safe decisions without needing to understand every internal detail of the BQ76952 or microcontroller firmware.
