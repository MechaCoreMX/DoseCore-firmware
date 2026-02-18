# Electrical Schematic

This directory contains the electrical connection diagram of the
**DoseCore: Programmable Medication Dispenser** prototype.

The schematic illustrates the complete wiring configuration between the
Arduino Mega 2560 and all peripheral components used in the system.

---

## Included File

### `DoseCore_electrical_diagram.pdf`

Electrical connection diagram of the full system, including:

- Arduino Mega 2560 (ATmega2560)
- DS3231 Real-Time Clock (RTC)
- 4×4 matrix keypad
- 16×2 LCD display (HD44780 compatible, 1602A)
- 360° continuous rotation servo motor
- LM2596 DC–DC voltage regulator
- Reed switches (compartment positioning sensors)
- Buzzer
- Potentiometer (LCD contrast control)
- External 12 V power supply

---

## System Architecture Overview

The system is centered around the Arduino Mega 2560 microcontroller,
which manages:

- Time-based scheduling via the DS3231 RTC (I2C interface: SDA/SCL)
- User input through the 4×4 matrix keypad
- Visual feedback using the 16×2 LCD (4-bit parallel mode)
- Mechanical actuation through a 360° servo motor
- Compartment position detection using reed switches
- Audible alerts via buzzer

The servo motor is powered through an LM2596 DC–DC regulator supplied
by an external 12 V source.

---

## Power Distribution

- Logic supply: 5 V from Arduino Mega 2560
- External supply: 12 V DC input
- Servo powered via regulated DC–DC module (LM2596)
- All grounds (GND) are common and shared

Proper grounding between the Arduino and external power stage is
required to ensure stable operation.

---

## Interface Details

### I2C Communication
- DS3231 connected via SDA and SCL lines

### LCD (16×2, 4-bit mode)
- RS, E, D4–D7 connected to digital pins
- Potentiometer used to adjust display contrast

### Keypad
- 4 row lines and 4 column lines connected to digital pins

### Reed Switches
- Configured as digital inputs (active-low with internal pull-up)

### Servo
- Controlled through a PWM-capable digital pin

---

## Reproducibility

This schematic reflects the exact wiring configuration used to collect
the experimental data reported in the associated manuscript.

The firmware in the root directory of this repository corresponds
directly to the pin mapping represented in this schematic.

---

## Notes

- Minor adjustments may be required depending on hardware revisions.
- Always verify voltage levels before powering the system.
- The schematic represents the research prototype configuration.
