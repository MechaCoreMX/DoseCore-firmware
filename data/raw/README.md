# Raw Experimental Data

This directory contains the raw experimental measurements collected during the
validation of the **DoseCore: Programmable Medication Dispenser**.

The dataset includes mechanical positioning error and electrical consumption
measurements recorded across multiple actuation cycles.

---

## File Description

### `experimental_data.csv`

This file contains raw measurements obtained from 100 independent actuation
cycles of the device.

Each row corresponds to a single cycle and includes the following variables:

- `cycle` — Sequential cycle identifier  
- `angular_error` — Absolute angular positioning error (degrees)  
- `idle_current` — Current consumption in rest condition (mA)  
- `peak_current` — Maximum current recorded during actuation (mA)  
- `success` — Binary indicator of successful compartment alignment (1 = success, 0 = failure)  

---

## Experimental Conditions

- Total cycles evaluated: 100  
- Actuation performed under controlled laboratory conditions  
- Angular error measured relative to the expected compartment alignment position  
- Electrical measurements acquired during steady rest and peak actuation phases  

---

## Usage

This dataset serves as the basis for computing the statistical performance
metrics located in:

data/processed/summary_metrics.csv


All summary statistics reported in the associated manuscript are derived from
this raw dataset using the analysis notebook:

analysis/performance_analysis.ipynb


---

## Notes

The data provided in this directory represent unprocessed measurements and
are included to ensure full reproducibility and scientific transparency.
