# Linear Regression Lab

Laboratory work on **simple and multiple linear regression** using `scikit-learn`.

## Datasets

1. **Head Brain** — simple linear regression (1 feature: head size → brain weight)
2. **India House Rent** — multiple linear regression (features: bathrooms, beds, balconies → rent)

> Both datasets are loaded automatically via `kagglehub`.

## Objectives

- Apply simple and multiple linear regression models
- Split data into train/test (80/20)
- Extract model parameters (slope, intercept)
- Evaluate models with **MAE**, **MSE**, **RMSE**, **R²**
- Run experiments with different feature combinations
- Compare results in a single summary table

## Experiments (Multiple Regression)

| Experiment | Features |
|------------|----------|
| A          | bathrooms |
| B          | bathrooms + beds |
| C          | bathrooms + beds + balconies |

The target variable `rent` was log-transformed (`log1p`) to reduce skewness. Metrics are reported both in log-scale and in the original scale (via `expm1`).

## Key Results

- **Simple regression (Head Brain):** R² ≈ 0.71
- **Multiple regression (House Rent):** R² increases as more informative features are added (A < B < C)

## Tech Stack

- Python 3
- pandas, numpy
- scikit-learn
- matplotlib, seaborn
- kagglehub
