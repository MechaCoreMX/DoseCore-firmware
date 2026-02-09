# DoseCore: Programmable Medication Dispenser – Firmware

This repository contains the firmware source code for **DoseCore: Programmable
Medication Dispenser**, a smart and programmable pillbox designed to support
medication adherence through scheduled alarms and controlled mechanical
dispensing.

The system is implemented using an Arduino Mega 2560 and integrates a real-time
clock, user interface, acoustic alerts, and a servo-driven dispensing mechanism.
The firmware is part of an academic research project currently under editorial
review for publication in *HardwareX*.

---

## System Overview

DoseCore is a low-cost, microcontroller-based assistive device aimed at improving
medication management, particularly for elderly users and patients with chronic
conditions. The system combines time-based scheduling with a mechanical dispensing
mechanism and a simple human–machine interface.

The firmware is responsible for:
- Time monitoring and alarm scheduling
- User interaction via keypad and LCD
- Servo-based compartment positioning
- Safe and repeatable dispensing actions

---

## Hardware Platform

- **Microcontroller:** Arduino Mega 2560  
- **Actuator:** 360° continuous rotation servomotor (DS04-NFC)  
- **Positioning:** Neodymium magnet and reed switches  
- **User interface:** 4×4 matrix keypad, 16×2 LCD display  
- **Timing:** DS3231 Real-Time Clock (RTC)  
- **Audio feedback:** Buzzer  
- **Power:** External 12 V supply with DC–DC regulation  
- **Mechanical parts:** 3D-printed PLA components  

---

## Bill of Materials (BOM)

| ID | Component | Qty | Unit Cost (USD) |
|----|----------|-----|-----------------|
| H | Arduino Mega 2560 | 1 | 24.50 |
| D | 360° servomotor DS04-NFC | 1 | 2.72 |
| I | LM2596 DC–DC regulator | 1 | 1.02 |
| J | DS3231 RTC module | 1 | 1.02 |
| K | Buzzer | 1 | 1.02 |
| F | Reed switch (N.O.) | 4 | 1.02 |
| C | 4×4 matrix keypad | 1 | 1.02 |
| E | 16×2 LCD (HD44780) | 1 | 1.02 |
| L | Potentiometer 10 kΩ | 1 | 2.89 |
| M | Resistor 220 Ω | 1 | 1.02 |
| B | Neodymium magnet (6 × 3 mm) | 1 | 1.02 |
| N | 12 V – 3 A power supply | 1 | 1.02 |
| A,G | 3D-printed parts (PLA, ~150 g) | — | 8.00 |

---

## Repository Structure (Arduino IDE Compatible)

All files are located in the root folder to ensure compatibility with the
**Arduino IDE**, which does not compile nested source directories by default.

```text
DoseCore/
├── main.ino        # Firmware entry point (setup and loop)
├── pins.h          # Hardware pin mapping
├── config.h        # Global configuration and timing parameters
├── types.h         # Data structures and enumerations
├── globals.h       # Global declarations
├── globals.cpp     # Global object instantiation
├── motion.h        # Motion control interface
├── motion.cpp      # Servo and positioning logic
├── ui.h            # User interface interface
├── ui.cpp          # LCD and keypad implementation
├── alarm.h         # Alarm system interface
├── alarm.cpp       # Alarm and dispensing logic
├── README.md
├── LICENSE
└── CITATION.cff
