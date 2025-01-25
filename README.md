# Motor Control System

## Overview
The Motor Control System is an automotive embedded project designed to monitor motor temperature and manage system faults. The system uses two ECUs communicating over CAN, ensuring reliability and fault management through a robust diagnostic and communication mechanism.

### Objectives:
1. Monitor motor temperature and identify faults.
2. Communicate system health to a PC via UART.
3. Manage faults, including communication loss, temperature anomalies, and diagnostic trouble codes (DTCs).

---

## System Description

### Components:
1. **ECU1 (System Health Monitor):**
   - Communicates with the PC via UART.
   - Sends a keep-alive message to ECU2 every 100ms.
   - Determines if motor temperature readings are within the normal range.
   - Performs ADC health checks when needed.
   - Manages fault states and DTCs.

2. **ECU2 (Motor Monitor):**
   - Monitors motor temperature using an ADC.
   - Averages ADC readings and sends data to ECU1 over CAN every 500ms.
   - Responds to ECU1’s diagnostic and fault-check requests.

---

## Functional Requirements

### ECU1 Responsibilities:
- **UART Communication:**
  - Report system data to the PC every second.
  - Enter and exit diagnostic mode (tester mode) using UART commands.
- **CAN Communication:**
  - Send keep-alive messages to ECU2 every 100ms.
  - Receive motor temperature readings from ECU2.
- **Fault Management:**
  - If no temperature reading is received for 3 seconds, send an ADC health check remote frame to ECU2.
  - Enter fault state if ADC readings from ECU2 are invalid.
  - Save DTCs for overheat or communication loss after 3 consecutive occurrences.

### ECU2 Responsibilities:
- **Motor Monitoring:**
  - Read motor temperature using ADC.
  - Average multiple ADC readings to ensure accuracy.
  - Send averaged temperature data to ECU1 every 500ms.
- **Fault Response:**
  - Respond to ADC health check requests from ECU1.
  - Enter diagnostic mode upon receiving the appropriate CAN message from ECU1.

---

## Fault Checks and LED Indications

### Fault States:
1. **Overheat:**
   - If ECU1 detects temperatures outside the 10-25°C range for 3 consecutive seconds:
     - Sends an ADC health check request to ECU2.
     - If ECU2’s ADC response is invalid:
       - Both ECUs blink red LEDs and stop communication.
       - Fault state saved in non-volatile memory.
     - If ADC response is valid, the motor is shut down, and both ECUs blink white LEDs for 10 seconds.

2. **Communication Lost:**
   - If an ECU does not receive a keep-alive message for 5 seconds:
     - Enter communication lost mode (blue LED blinks for 10 seconds).
     - Retry mechanism on ECU1 for 30 seconds before reporting failure to the PC.

### Diagnostic Trouble Codes (DTCs):
- **Overheat DTC:** Triggered after 3 consecutive overheat events.
- **Communication Lost DTC:** Triggered after 3 consecutive communication failures.
- **Fault State DTC:** Triggered if any invalid ADC response or system fault is detected.
- **DTC Management:**
  - DTCs can be cleared through the PC in diagnostic mode.

---

## Diagnostic Mode (Tester Mode)
- Entered through UART commands from the PC.
- Capabilities include:
  1. Clearing and monitoring DTCs.
  2. Querying ADC readings (via ECU2).
  3. Manipulating GPIOs on both ECUs.
- **LED Indications:**
  - On entering or exiting diagnostic mode, both ECUs blink white LEDs twice.
  - If communication is lost during diagnostic mode, ECU1 blinks blue LEDs while retrying communication for 30 seconds.

---

## Non-Functional Requirements

### Coding Standards:
- Code must be MISRA-compliant.
- Free from compilation warnings (excluding register files).
- Documented with file, function, and line comments.

### Documentation:
- Each component should have:
  - Source file and header file.
  - API table for each function with input, output, and description.
  - Flowcharts describing system behavior.

---

