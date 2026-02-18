# System Architecture and Functional Documentation

This directory contains high-level architectural and functional diagrams
of the **DoseCore: Programmable Medication Dispenser** system.

These documents describe both the global system structure and the detailed
firmware control logic implemented in the device.

---

## Included Files

### 1. `DoseCore_system_architecture.pdf`

This document presents the high-level system architecture, including:

- Overall system workflow
- Interaction between hardware and firmware modules
- Alarm scheduling and execution overview
- User interaction sequence
- Mechanical dispensing process

This diagram provides a conceptual understanding of how the system operates
as an integrated hardware–software platform.

---

### 2. `DoseCore_firmware_flowchart.pdf`

This document contains the detailed firmware control flow, including:

- System initialization procedure
- RTC configuration and validation
- Alarm comparison logic
- Buzzer activation
- Servo actuation control
- Reed switch feedback verification
- Compartment positioning sequence
- Return-to-home logic

This diagram reflects the logic implemented in the firmware source files:

main.ino
alarm.cpp
motion.cpp
ui.cpp


---

## Purpose

These documents support the reproducibility of the firmware behavior and
complement the following repository sections:

- Electrical schematics (`hardware/schematics/`)
- 3D printable parts (`hardware/stl/`)
- Experimental dataset (`data/`)
- Source firmware implementation (root directory)

---

## Notes

The diagrams represent the research prototype configuration described in the
associated HardwareX manuscript. Minor implementation details may vary in
future firmware revisions.
