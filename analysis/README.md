# Performance Analysis Notebook

This directory contains the computational analysis used to evaluate the
mechanical accuracy and electrical performance of the
**DoseCore: Programmable Medication Dispenser**.

The analysis reproduces all statistical metrics reported in the associated
HardwareX manuscript.

---

## Included File

### `performance_analysis.ipynb`

Jupyter Notebook used to:

- Load the raw experimental dataset
- Compute angular positioning statistics
- Calculate success rate
- Estimate mean and standard deviation of currents
- Determine the 95th percentile (P95) angular error
- Generate processed performance metrics

The notebook processes the dataset located in:

data/raw/experimental_data.csv


and produces the summary metrics stored in:

data/processed/summary_metrics.csv


---

## Computed Metrics

The notebook calculates:

### Mechanical Performance
- Total number of cycles (`n_cycles`)
- Success rate
- Mean angular error
- Standard deviation of angular error (σ)
- 95th percentile angular error (P95)
- Maximum angular error

### Electrical Performance
- Mean idle current
- Standard deviation of idle current
- Mean peak current
- Standard deviation of peak current

---

## Requirements

The notebook was developed using:

- Python 3.x
- NumPy
- Pandas
- Matplotlib (if plots are generated)

Recommended installation:

```bash
pip install numpy pandas matplotlib
