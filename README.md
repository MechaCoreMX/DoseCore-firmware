# DoseCore: Programmable Medication Dispenser – Firmware

This repository contains the **firmware source code** for **DoseCore: Programmable
Medication Dispenser**, a smart, programmable pillbox designed for digital
medication management.

DoseCore is a low-cost, microcontroller-based assistive device that automates
medication dispensing through scheduled alarms, controlled mechanical actuation,
and a user-friendly interface. The system is described in detail in a manuscript
currently under review for publication in *HardwareX*.

This repository provides the software layer required to reproduce the functional
behavior of the device, in accordance with open science and reproducible hardware
principles.

---

## Hardware in Context

Medication non-adherence represents a major challenge in healthcare, particularly
for elderly patients and individuals with chronic conditions. DoseCore addresses
this problem through a compact, programmable medication dispenser that combines
mechanical dispensing, real-time scheduling, and audiovisual alerts.

Unlike commercial smart pill dispensers, DoseCore is designed as an open and
modifiable system, emphasizing affordability, simplicity of use, and transparency
of design.

---

## System Overview

DoseCore consists of:
- A cylindrical mechanical structure with three medication compartments
- A rotating top cover driven by a 360° servomotor
- Magnetic indexing using a neodymium magnet and reed switches
- A microcontroller-based control unit
- A user interface based on an LCD display and matrix keypad
- Audible feedback through a buzzer
- Real-time scheduling via an RTC module

The firmware manages system initialization, alarm scheduling, user interaction,
servo positioning, and safety states.

---

## Hardware Platform

- **Microcontroller:** Arduino Mega 2560  
- **Actuator:** 360° continuous rotation servomotor (DS04-NFC)  
- **Positioning system:** Neodymium magnet + reed switches  
- **User interface:** 4×4 matrix keypad, 16×2 LCD (HD44780)  
- **Timing:** DS3231 real-time clock (RTC)  
- **Audio feedback:** Passive buzzer  
- **Power system:** 12 V AC/DC power supply with LM2596 DC–DC regulation  
- **Mechanical structure:** 3D-printed PLA components  

---

## Bill of Materials (BOM)

The following table summarizes the main components required to build the DoseCore
prototype. Costs are indicative and may vary depending on supplier and region.

| ID | Component | Qty | Unit Cost (USD) |
|----|----------|-----|-----------------|
| H | Arduino Mega 2560 microcontroller | 1 | 24.50 |
| D | 360° servomotor DS04-NFC | 1 | 2.72 |
| I | LM2596 DC–DC regulator module | 1 | 1.02 |
| J | DS3231 RTC module | 1 | 1.02 |
| K | Passive buzzer | 1 | 1.02 |
| F | Reed switch (Normally Open) | 4 | 1.02 |
| C | 4×4 matrix keypad | 1 | 1.02 |
| E | 16×2 LCD display (HD44780) | 1 | 1.02 |
| L | Potentiometer 10 kΩ | 1 | 2.89 |
| M | Resistor 220 Ω | 1 | 1.02 |
| B | Neodymium magnet (6 × 3 mm) | 1 | 1.02 |
| N | AC/DC power supply 12 V – 3 A | 1 | 1.02 |
| A, G | 3D printed parts (PLA, ~150 g) | — | 8.00 |

---

## Repository Structure

```text
firmware/
├── src/            # C source files
├── include/        # Header files
├── README.md
├── LICENSE
└── CITATION.cff
