# DoseCore: Programmable Medication Dispenser

DoseCore is a programmable medication dispensing system designed to improve
medication adherence through scheduled alarms and controlled mechanical
compartment positioning.

This repository contains the complete research prototype, including:

- Embedded firmware (Arduino Mega 2560)
- Electrical schematics
- 3D-printable enclosure files (STL)
- Experimental validation dataset
- Statistical performance analysis notebook
- System architecture documentation

The project is currently under editorial review for publication in *HardwareX*.

---

# System Overview

DoseCore is a low-cost, microcontroller-based assistive device aimed at
supporting elderly users and patients with chronic conditions who require
scheduled medication intake.

The system integrates:

- Real-time clock (RTC-based scheduling)
- Servo-driven compartment positioning
- Reed switch feedback verification
- Keypad and LCD human–machine interface
- Audible alarm notification

The firmware ensures safe, repeatable, and verifiable dispensing actions.

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

The following table lists the main components required to assemble the
**DoseCore: Programmable Medication Dispenser** prototype.  
All costs are indicative and provided for reference only.

| Component | Qty. | Unit cost (USD) | Total cost (USD) | Supplier | Material |
|----------|------|------------------|------------------|----------|----------|
| Arduino Mega 2560 microcontroller | 1 | 24.50 | 24.50 | AliExpress | Microcontroller |
| 360° servomotor DS04-NFC | 1 | 2.72 | 2.72 | AliExpress | Electronic |
| LM2596 DC–DC regulator module | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| DS3231 RTC module | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| Passive buzzer | 1 | 0.10 | 0.10 | AliExpress | Electronic |
| Reed switch (Normally Open) | 4 | 0.102 | 0.408 | AliExpress | Electronic |
| 4×4 matrix keypad | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| 16×2 LCD display (HD44780 compatible) | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| Potentiometer 10 kΩ | 1 | 2.89 | 2.89 | AliExpress | Electronic |
| Resistor 220 Ω | 1 | 0.051| 0.051 | AliExpress | Electronic |
| Neodymium magnet (6 × 3 mm) | 1 | 0.102 | 0.102 | AliExpress | Electronic |
| AC/DC power supply 12 V – 3 A | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| 3D-printed parts set (PLA) | ~150 g | 0.008 | 1.20 | AliExpress | Mechanical / Structural |
| 3Coil of 30 AWG copper wire (10 m) | 5 | 0.102 | 0.51 | AliExpress | Conductor |

**Note:** Prices correspond to typical online suppliers and may vary depending on
region, availability, and purchase volume.

---

## Dependencies (Arduino Libraries)

The firmware was developed and tested using the **Arduino IDE** and requires the
following libraries to be installed before compilation.

### Required Libraries
Install the following libraries using the **Arduino Library Manager**
(`Sketch → Include Library → Manage Libraries`):

- **RTClib** (by Adafruit)  
  Used for communication with the DS3231 real-time clock module.

- **Keypad**  
  Provides support for scanning and decoding input from the 4×4 matrix keypad.

- **LiquidCrystal**  
  Handles the 16×2 LCD display (HD44780 compatible).  
  *(This library is included by default with the Arduino IDE.)*

- **Servo**  
  Used to control the continuous rotation servomotor.  
  *(This library is included by default with the Arduino IDE.)*

### Development Environment
- **Arduino IDE:** Version 2.x  
- **Target board:** Arduino Mega 2560  
- **Framework:** Arduino

### Notes
All third-party libraries can be installed directly from the Arduino Library
Manager. No additional external software dependencies are required to build
or run the firmware.

---

## Wiring / Pinout (Arduino Mega 2560)

This section provides a high-level overview of the electrical connections used in
the **DoseCore: Programmable Medication Dispenser** prototype.  
The authoritative and complete pin mapping is defined in the `pins.h` file.

### Actuators and Indicators
- **Servo motor (continuous rotation):** Digital pin **6**  
- **Buzzer:** Analog pin **A3** (configured as digital output)

### Positioning Sensors
All reed switches are configured as `INPUT_PULLUP` and are therefore
**active-low** (triggered when the signal is pulled to ground).

- **Home position reed switch:** Digital pin **7**  
- **Compartment A reed switch:** Digital pin **3**  
- **Compartment B reed switch:** Digital pin **4**  
- **Compartment C reed switch:** Digital pin **5**

### LCD Display (16×2, HD44780 compatible, parallel mode)
The LCD is connected in 4-bit parallel mode.

- **RS:** Digital pin **42**  
- **E:** Digital pin **44**  
- **D4:** Digital pin **46**  
- **D5:** Digital pin **48**  
- **D6:** Digital pin **50**  
- **D7:** Digital pin **52**

### Matrix Keypad (4×4)
- **Row pins:** Digital pins **22, 24, 26, 28**  
- **Column pins:** Digital pins **30, 32, 34, 36**

### Power
- **Logic supply:** 5 V provided by the Arduino Mega 2560  
- **External supply:** 12 V DC (used for the servo motor and power stage)

### Notes
- All pin assignments are centralized in `pins.h` to simplify hardware changes
  and improve reproducibility.
- Ground (GND) must be shared between the Arduino Mega 2560 and the external
  power supply.

---

# Repository Structure

```text
DoseCore/
│
├── main.ino
├── pins.h
├── config.h
├── types.h
├── globals.h
├── globals.cpp
├── motion.cpp / motion.h
├── ui.cpp / ui.h
├── alarm.cpp / alarm.h
│
├── hardware/
│   ├── schematics/
│   │   ├── diagrama.pdf
│   │   └── README.md
│   │
│   └── stl/
│       ├── Pillbox case body.STL
│       ├── Pillbox case low.STL
│       ├── Pillbox case top.STL
│       └── README.md
│
├── docs/
│   ├── DoseCore_system_architecture.pdf
│   ├── DoseCore_firmware_flowchart.pdf
│   └── README.md
│
├── data/
│   ├── raw/
│   │   ├── experimental_data.csv
│   │   └── README.md
│   │
│   ├── processed/
│   │   ├── summary_metrics.csv
│   │   └── README.md
│   │
│   └── README.md
│
├── analysis/
│   ├── performance_analysis.ipynb
│   └── README.md
│
├── legacy/
│   ├── Code-V1.ino
│   ├── Code-V2.ino
│   └── README.md
│
├── LICENSE
├── CITATION.cff
└── README.md
```

---

# Hardware Description

## Core Components

The DoseCore prototype is built around a modular embedded architecture
integrating mechanical, electronic, and control subsystems.

- **Microcontroller:** Arduino Mega 2560  
- **Actuator:** 360° continuous rotation servo motor (DS04-NFC)  
- **Position Feedback:** Reed switches (active-low configuration)  
- **User Interface:** 4×4 matrix keypad and 16×2 LCD (HD44780 compatible)  
- **Timing Module:** DS3231 Real-Time Clock (RTC)  
- **Power Supply:** 12 V external source with LM2596 DC–DC regulator  
- **Enclosure:** Custom 3D-printed PLA structure  

The complete electrical wiring diagram is provided in:

hardware/schematics/diagrama.pdf

3D printable enclosure components are available in:

hardware/stl/

---

# Firmware

The firmware is modular and organized into dedicated components for:

- Motion control
- Alarm management
- User interface handling
- Hardware abstraction

It is fully compatible with **Arduino IDE 2.x**.

### Required Libraries

Install using the Arduino Library Manager:

- RTClib (Adafruit)
- Keypad
- LiquidCrystal
- Servo

---

# Experimental Validation

The repository includes complete experimental validation data to ensure
scientific reproducibility.

## Raw Dataset

Located at:

data/raw/experimental_data.csv

The dataset includes 100 actuation cycles with measurements of:

- Angular positioning error (degrees)
- Idle current (mA)
- Peak current during actuation (mA)
- Success indicator (binary)

---

## Processed Metrics

Located at:

data/processed/summary_metrics.csv

The computed performance indicators include:

- Total cycles (n = 100)
- Success rate (100%)
- Mean angular error: 2.52°
- Standard deviation: 1.43°
- 95th percentile error: ~4.75°
- Maximum angular error: 5°
- Mean idle current: 90 mA
- Mean peak current: 479.2 mA

---

# Performance Analysis

The statistical analysis used to compute these metrics is available in:

analysis/performance_analysis.ipynb


Running the notebook reproduces all summary statistics reported in
`summary_metrics.csv`.

---

# Reproducibility

## Firmware

1. Clone or download the repository.
2. Install required Arduino libraries.
3. Open `main.ino` in Arduino IDE.
4. Select board: Arduino Mega 2560.
5. Compile and upload.

## Experimental Metrics

1. Ensure dataset is located in `data/raw/`.
2. Open `analysis/performance_analysis.ipynb`.
3. Run all cells sequentially.

The computed values should match those in
`data/processed/summary_metrics.csv`.

---

# Code Availability

The actively maintained firmware version is hosted on GitHub.

A stable release corresponding to the manuscript is archived on Zenodo
and assigned a DOI to ensure long-term preservation and citation.

Citation metadata is provided in the `CITATION.cff` file.

---

# License

This software is released under the **Apache License 2.0**.

The license permits academic and commercial use, modification, and
redistribution, provided that proper attribution is maintained.

See the `LICENSE` file for the complete license text.

---

# Intellectual Property Notice

This firmware is associated with a hardware system for which a patent
application is currently under evaluation.

The open-source distribution of this software does **not** grant rights
to manufacture, commercialize, or reproduce the associated hardware
design without authorization from the authors.

This repository is intended for scientific transparency, academic
dissemination, and reproducibility of the research prototype.

---

# Legacy Code

The `legacy/` directory contains earlier monolithic firmware versions
used during initial prototyping.

These files are provided for historical reference only and are not
required to compile or operate the current firmware version.
