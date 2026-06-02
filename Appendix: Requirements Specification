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

**SRS 01** – The software shall communicate with the BQ76952 battery monitor IC using the I2C protocol.

**SRS 02** – The software shall read the voltage of each connected battery cell from the BQ76952.

**SRS 03** – The software shall compare each cell voltage to a programmed minimum and maximum safe voltage threshold.

**SRS 04** – The software shall identify an undervoltage fault when any cell voltage falls below the programmed minimum voltage threshold.

**SRS 05** – The software shall identify an overvoltage fault when any cell voltage rises above the programmed maximum voltage threshold.

**SRS 06** – The software shall include a voltage tolerance margin to reduce false fault detection caused by electrical noise or small measurement errors.

**SRS 07** – The software shall read battery pack current using the shunt voltage measurement provided by the BQ76952.

**SRS 08** – The software shall identify an overcurrent fault when the measured current exceeds the programmed safe current limit.

**SRS 09** – The software shall read temperature data from the BQ76952 or connected temperature sensors.

**SRS 10** – The software shall identify a temperature fault when the measured temperature is outside the programmed safe operating range.

**SRS 11** – The software shall read protection status registers from the BQ76952 to determine if a fault condition has occurred.

**SRS 12** – The software shall report battery status information, including cell voltages, current, temperature, and fault states.

**SRS 13** – The software shall support fault handling by disabling or warning against unsafe charging or discharging conditions.

**SRS 14** – The software shall initialize the BQ76952 before normal battery monitoring begins.

**SRS 15** – The software should support cell balancing control to reduce voltage differences between cells.

**SRS 16** – The software should allow safety thresholds to be adjusted in firmware for testing and calibration.

**SRS 17** – The software shall not ignore critical fault conditions reported by the BQ76952.

**SRS 18** – The software shall not allow normal battery operation to continue if a serious protection fault is active.

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

**HRS 01** – The hardware shall use the BQ76952 battery monitor IC as the main battery monitoring device.

**HRS 02** – The hardware shall support monitoring of a battery pack containing 3 to 16 series-connected cells.

**HRS 03** – The hardware shall provide individual cell voltage connections from the battery pack to the BQ76952.

**HRS 04** – The hardware shall allow the BQ76952 to measure each individual cell voltage.

**HRS 05** – The hardware shall include a shunt resistor in the negative current path of the battery pack for current measurement.

**HRS 06** – The hardware shall allow the BQ76952 to measure the voltage across the shunt resistor.

**HRS 07** – The hardware shall support current measurement during charging and discharging.

**HRS 08** – The hardware shall include temperature sensing components to monitor battery pack temperature.

**HRS 09** – The hardware shall include I2C connections between the microcontroller and the BQ76952.

**HRS 10** – The hardware shall include pull-up resistors on the I2C communication lines if required by the circuit design.

**HRS 11** – The hardware shall include protection circuitry for unsafe battery conditions such as overvoltage, undervoltage, overcurrent, and short circuit events.

**HRS 12** – The hardware shall support high-side NFET control for battery pack protection.

**HRS 13** – The hardware shall allow the BQ76952 to disconnect or protect the battery pack during critical fault conditions.

**HRS 14** – The hardware shall support cell balancing connections for reducing voltage differences between cells.

**HRS 15** – The hardware shall be powered from the battery pack or an appropriate regulated supply.

**HRS 16** – The hardware shall include appropriate connectors for the battery cells, microcontroller, communication lines, and measurement points.

**HRS 17** – The hardware shall not allow battery cells to be connected in a way that exceeds the supported voltage range of the BQ76952.

**HRS 18** – The hardware shall not bypass the current-sense shunt when current measurement is required.

**HRS 19** – The hardware should include test points for cell voltage, pack voltage, current sense, ground, and communication signals.

**HRS 20** – The hardware should be designed so that battery monitoring and protection can continue without requiring constant user input.
