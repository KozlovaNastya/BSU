# Ensemble Methods Lab — Bagging, Boosting & Stacking

Laboratory work on **ensemble methods for classification** using `scikit-learn`, `XGBoost` and `LightGBM`.

Compares classical models (Lab #4) with three ensemble types on two datasets: **Wine Quality** (multiclass) and **Telco Customer Churn** (binary).


## Datasets (same as Lab #4)

### Dataset №1 — Wine Quality (multiclass)
- **Source:** Kaggle (`yasserh/wine-quality-dataset`)
- **Task:** Predict wine quality score (3–8) from 11 physicochemical features
- **Rows:** 1143 | **Features:** 11 (all numeric) | **Classes:** 6
- **Note:** Classes re-encoded to `0..5` via `LabelEncoder` (XGBoost/LightGBM requirement)

### Dataset №2 — Telco Customer Churn (binary)
- **Source:** Kaggle (`blastchar/telco-customer-churn`)
- **Task:** Predict whether a customer will churn (Yes/No)
- **Rows:** 7043 | **Features:** 19 (4 numeric + 15 categorical) | **Classes:** 2
- **Note:** Class imbalance ~73/27 — handled via `class_weight='balanced'` and `scale_pos_weight`

Both datasets are loaded automatically via `kagglehub`.


## Objectives

1. Apply **three types of ensembles**:
   - **Bagging:** `RandomForestClassifier`, `BaggingClassifier`
   - **Boosting:** `XGBoost`, `LightGBM` (**not** sklearn's `GradientBoostingClassifier`)
   - **Stacking:** `StackingClassifier` (SVM + DT + RF → LogisticRegression)
2. Reuse the same train/test split (`random_state=42`) and preprocessing pipelines from Lab #4
3. Tune critical hyperparameters (`n_estimators`, `learning_rate`, `max_depth`)
4. Evaluate with **Confusion Matrix**, **Classification Report**, **F1-score**
5. Compare results against classical models from Lab #4 in a global summary table


## Methodology

### Preprocessing (identical to Lab #4)
| Feature type | Transformation |
|---|---|
| Numeric (Wine: all; Churn: 4) | `SimpleImputer(median)` + `StandardScaler` |
| Categorical (Churn: 15) | `SimpleImputer(most_frequent)` + `OneHotEncoder(drop='first')` |

All preprocessing wrapped in a **Pipeline** for Churn to prevent data leakage.

### Ensembles
| Type | Model | Key Hyperparameters |
|---|---|---|
| Bagging | RandomForest | `n_estimators`, `max_depth`, `min_samples_leaf` |
| Bagging | BaggingClassifier | `n_estimators`, `max_samples`, `max_features` |
| Boosting | XGBoost | `n_estimators`, `learning_rate`, `max_depth` |
| Boosting | LightGBM | `n_estimators`, `learning_rate`, `num_leaves` |
| Stacking | SVM + DT + RF → LogReg | `cv=5`, `stack_method='predict_proba'` |

### Scoring
- **Wine** → `f1_weighted` (6 classes, imbalanced)
- **Churn** → `f1` (binary, focus on minority class)


## Key Results

### Wine Quality (multiclass) — best models

| Model | Accuracy | F1 (weighted) | Type |
|---|---|---|---|
| SVM (Lab #4) | 0.6681 | 0.6420 | classic |
| RandomForest (tuned) | 0.7118 | 0.6893 | bagging |
| **BaggingClassifier** | **0.7293** | **0.7089** | 🏆 bagging |
| XGBoost (tuned) | 0.6638 | 0.6507 | boosting |
| LightGBM (tuned) | 0.6725 | 0.6599 | boosting |
| Stacking | 0.7205 | 0.6975 | stacking |

**Insight:** Bagging beat boosting on Wine. Reason: dataset is small (1143 rows) — boosting needs more data to shine. Deep trees on all features (Bagging) outperform randomized trees (RandomForest) on this small feature set.

### Telco Churn (binary) — best models

| Model | Accuracy | Precision | Recall | F1 | Type |
|---|---|---|---|---|---|
| DT (Lab #4) | 0.7410 | 0.5077 | 0.7941 | 0.6194 | classic |
| **RandomForest (tuned)** | 0.7601 | 0.5327 | 0.7834 | **0.6342** | 🏆 bagging |
| XGBoost (tuned) | 0.7360 | 0.5016 | **0.8235** | 0.6235 | boosting |
| LightGBM (tuned) | 0.7544 | 0.5247 | 0.7941 | 0.6319 | boosting |
| Stacking | 0.7523 | 0.5222 | 0.7861 | 0.6275 | stacking |

**Insight:** All ensembles are within ~1% of each other on F1. **XGBoost tuned** has the highest Recall (0.8235) — best for business (minimizing missed churners). **RandomForest tuned** has the best F1.


## Tech Stack

- Python 3
- `pandas`, `numpy` — data manipulation
- `scikit-learn` — preprocessing, Pipelines, classical models, Bagging, Stacking, metrics
- `xgboost`, `lightgbm` — gradient boosting (production libraries)
- `matplotlib`, `seaborn` — visualization
- `kagglehub` — dataset download


## Conclusions

1. **Ensembles beat classical models** on both datasets — F1 improved from 0.6420 → 0.7089 on Wine, and 0.6194 → 0.6342 on Churn.
2. **Type of ensemble depends on the data:**
   - **Small data (Wine):** bagging wins — deep trees on all features, less risk of overfitting
   - **Larger data (Churn):** bagging and boosting are close; boosting wins on Recall
3. **Stacking is not a silver bullet** — on Wine it lost to plain BaggingClassifier, on Churn it came 2nd. Stacking works best when base models are *diverse and weak individually but strong in different aspects*.
4. **Accuracy is misleading on Churn** — MLP with highest Accuracy (0.789) had the lowest F1 (0.5605). F1 and Recall reveal the real quality.
5. **Class imbalance matters:** `class_weight='balanced'` and `scale_pos_weight` improved minority-class Recall significantly.
6. **No free lunch:** there is no universal best algorithm — ensemble choice depends on dataset size, feature count, and business metric priority.