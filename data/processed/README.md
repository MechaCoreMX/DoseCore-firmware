# Processed Performance Metrics

This directory contains the statistical performance indicators derived from the
raw experimental dataset used to validate the operation of the
**DoseCore: Programmable Medication Dispenser**.

The metrics summarize the angular positioning accuracy and electrical
performance of the device across 100 actuation cycles.

---

## File Description

### `summary_metrics.csv`

This file contains aggregated statistical metrics computed from the raw dataset
located in:

data/raw/experimental_data.csv


Each row includes:

- `metric` — Name of the performance indicator  
- `value` — Computed numerical result  
- `unit` — Measurement unit (degrees, mA, percent, cycles)  
- `description` — Brief explanation of the metric  

---

## Reported Metrics

### Mechanical Performance

- **n_cycles** — Total number of actuation cycles evaluated (100 cycles)  
- **success_rate** — Percentage of successful compartment alignments (100%)  
- **mean_angular_error** — Average angular positioning error (2.52°)  
- **std_angular_error (σ)** — Standard deviation of angular positioning error (1.43°)  
- **p95_angular_error** — 95th percentile of angular positioning error (~4.75°)  
- **max_angular_error** — Maximum observed angular error (5°)  

### Electrical Performance

- **mean_idle_current** — Average current consumption at rest (90 mA)  
- **std_idle_current (σ)** — Standard deviation of idle current (0 mA)  
- **mean_peak_current** — Average peak current during actuation (479.2 mA)  
- **std_peak_current (σ)** — Standard deviation of peak current during actuation (14.54 mA)  

---

## Reproducibility

All metrics in this directory are computed using the analysis notebook:

analysis/performance_analysis.ipynb


Executing the notebook with the provided raw dataset will reproduce the
statistical results contained in `summary_metrics.csv`.

---

## Notes

These processed metrics correspond to the quantitative validation results
reported in the associated HardwareX manuscript and are provided to ensure
full scientific transparency, reproducibility, and long-term archival through
the Zenodo release associated with this repository.

