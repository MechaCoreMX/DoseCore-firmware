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

The following table lists the main components required to assemble the
**DoseCore: Programmable Medication Dispenser** prototype.  
All costs are indicative and provided for reference only.

| Component | Qty. | Unit cost (USD) | Total cost (USD) | Supplier | Material |
|----------|------|------------------|------------------|----------|----------|
| Arduino Mega 2560 microcontroller | 1 | 24.50 | 24.50 | AliExpress | Microcontroller |
| 360° servomotor DS04-NFC | 1 | 2.72 | 2.72 | AliExpress | Electronic |
| LM2596 DC–DC regulator module | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| DS3231 RTC module | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| Passive buzzer | 1 | 1.02 | 0.41 | AliExpress | Electronic |
| Reed switch (Normally Open) | 4 | 1.02 | 1.02 | AliExpress | Electronic |
| 4×4 matrix keypad | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| 16×2 LCD display (HD44780 compatible) | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| Potentiometer 10 kΩ | 1 | 2.89 | 2.89 | AliExpress | Electronic |
| Resistor 220 Ω | 1 | 1.02 | 0.05 | AliExpress | Electronic |
| Neodymium magnet (6 × 3 mm) | 1 | 1.02 | 0.10 | AliExpress | Electronic |
| AC/DC power supply 12 V – 3 A | 1 | 1.02 | 1.02 | AliExpress | Electronic |
| 3D-printed parts set (PLA) | ~150 g | 8.00 | 1.20 | AliExpress | Mechanical / Structural |

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

## Reproducibility

The following steps describe how to reproduce the firmware behavior of the  
**DoseCore: Programmable Medication Dispenser** using the Arduino IDE.

### 1. Obtain the Source Code
Clone or download the source code from the public GitHub repository associated
with this project. The repository can be accessed directly through the URL
provided in the project documentation.

Alternatively, the source code can be downloaded as a ZIP archive from the
GitHub repository page.

(`git clone https://github.com/MechaCoreMX/DoseCore-firmware.git`)

### 2. Install Dependencies
Open the **Arduino IDE** and install the required libraries using the  
**Library Manager** (`Sketch → Include Library → Manage Libraries`):

- **RTClib** (by Adafruit)  
- **Keypad**  
- **LiquidCrystal** (included by default with Arduino IDE)  
- **Servo** (included by default with Arduino IDE)

### 3. Open the Firmware
Open the file **`main.ino`** located in the root directory of the repository using
the Arduino IDE.

### 4. Select Target Hardware
In the Arduino IDE, configure the following options:

- **Board:** Arduino Mega 2560  
- **Processor:** ATmega2560  
- **Port:** Select the serial port corresponding to your board

### 5. Compile and Upload
Compile the firmware using the **Verify** function and then upload it to the
Arduino Mega 2560 using the **Upload** function.

### 6. Expected Startup Behavior
After powering the system, the following sequence should be observed:

1. The LCD initializes and displays a startup message.
2. The servo motor performs an automatic homing routine until the home reed
   switch is detected.
3. The system enters idle mode and displays the current date and time.
4. The firmware starts monitoring scheduled medication doses.

### 7. Basic Functional Test
To verify correct operation:

- Press **A**, **B**, or **C** on the keypad to manually open the corresponding
  compartment.
- Press **D** to enter the dose configuration menu.
- At a scheduled time, an audible alarm is triggered and the corresponding
  compartment is automatically exposed.

If the above behavior is observed, the firmware is considered to be operating
correctly.

---

## Code Availability

The firmware source code for **DoseCore: Programmable Medication Dispenser** is
publicly available through the project’s GitHub repository.

A stable release corresponding to the version described in the associated
scientific publication will be archived on **Zenodo** and assigned a **Digital
Object Identifier (DOI)** to ensure long-term accessibility and reproducibility.

The GitHub repository contains the actively maintained development version of the
firmware, while the Zenodo archive will serve as the permanent reference version
for citation purposes.

---

## License

This software is released under the **Apache License 2.0**.

The Apache License 2.0 permits use, modification, and redistribution of the
source code for both academic and commercial purposes, provided that proper
attribution is given and that any modifications are clearly documented.

A copy of the full license text is provided in the `LICENSE` file included in
this repository.

---

## Intellectual Property Notice

This firmware is associated with a hardware system for which a patent application
is currently under evaluation.

The publication and open-source distribution of this software do **not** grant
any rights to manufacture, commercialize, reproduce, or derive the associated
hardware design. All rights related to the physical device, mechanical structure,
and system-level integration remain reserved by the authors.

This repository is intended to support scientific transparency, reproducibility
of the firmware behavior, and academic dissemination, in accordance with the
licensing terms specified in this project.

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
