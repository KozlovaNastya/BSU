# Classification Lab — Wine Quality & Telco Customer Churn

Laboratory work on **binary and multiclass classification** using `scikit-learn`.  
Covers data preprocessing, hyperparameter tuning with `GridSearchCV`, model evaluation, and comparison of classical ML algorithms.

## Datasets

### Dataset №1 — Wine Quality (multiclass)
- **Source:** Kaggle (`yasserh/wine-quality-dataset`)
- **Task:** Predict wine quality score (3–8) from 11 physicochemical features
- **Rows:** 1143 | **Features:** 11 (all numeric) | **Classes:** 6
- **Class imbalance:** classes 5 and 6 make up ~82% of the data; classes 3, 4, 8 are rare

### Dataset №2 — Telco Customer Churn (binary)
- **Source:** Kaggle (`blastchar/telco-customer-churn`)
- **Task:** Predict whether a customer will churn (Yes/No)
- **Rows:** 7043 | **Features:** 19 (4 numeric + 15 categorical) | **Classes:** 2
- **Class imbalance:** ~73% No / ~27% Yes

Both datasets are loaded automatically via `kagglehub`.


## Objectives

1. Apply 4 classical classification algorithms:
   - **kNN** (k-Nearest Neighbors)
   - **Decision Tree**
   - **SVM** (Support Vector Machine)
   - **MLP** (Multi-Layer Perceptron / Neural Network)
2. Preprocess data properly:
   - `StandardScaler` for numeric features
   - `OneHotEncoder` for categorical features
   - `ColumnTransformer` + `Pipeline` to prevent data leakage
3. Split data with `stratify` to preserve class proportions
4. Tune hyperparameters with `GridSearchCV` (cross-validation)
5. Evaluate models with **Accuracy**, **Precision**, **Recall**, **F1-score**, and **Confusion Matrix**
6. Compare baseline (default parameters) vs tuned models

## Methodology

### Preprocessing
| Feature type | Transformation |
|---|---|
| Numeric (Wine: all; Churn: 4) | `SimpleImputer(median)` + `StandardScaler` |
| Categorical (Churn: 15) | `SimpleImputer(most_frequent)` + `OneHotEncoder(drop='first', handle_unknown='ignore')` |

All preprocessing is wrapped in a **Pipeline** so that scalers/encoders are fitted **only on the training fold** — this prevents data leakage during cross-validation.

### Hyperparameter tuning
- `GridSearchCV` with 5-fold cross-validation (MLP: 3-fold for speed)
- Scoring metric:
  - **Wine** → `f1_weighted` (6 classes, imbalanced)
  - **Churn** → `f1` (binary, focus on minority class)
- `class_weight='balanced'` used for Decision Tree and SVM on Churn to handle imbalance


## Key Results

### Wine Quality (multiclass)
- Best baseline: **SVM** (highest accuracy & F1)
- After tuning: SVM remains the strongest due to RBF kernel’s ability to separate close classes
- Main confusion: classes **5↔6** and **6↔7** — expected, since wines of adjacent grades are physically similar

### Telco Customer Churn (binary)
| Model | Accuracy | Precision | Recall | F1 |
|---|---|---|---|---|
| **Decision Tree** | 0.741 | 0.508 | **0.794** | **0.6194** |
| SVM | 0.734 | 0.499 | **0.794** | 0.6130 |
| kNN | **0.782** | 0.593 | 0.572 | 0.5823 |
| MLP | **0.789** | **0.625** | 0.508 | 0.5605 |

**Key finding:** MLP has the highest Accuracy (0.789) and Precision (0.625) but the lowest F1 (0.5605). Decision Tree has lower Accuracy (0.741) but the best F1 (0.6194) and Recall (0.794).  
→ **Accuracy is misleading under class imbalance.** For churn prediction, FN (missed churner) is 5–7× more expensive than FP, so **F1 and Recall matter more**.

## Tech Stack

- Python 3
- `pandas`, `numpy` — data manipulation
- `scikit-learn` — models, preprocessing, metrics, GridSearchCV
- `matplotlib`, `seaborn` — visualization
- `kagglehub` — dataset download

---

## Conclusions

1. **Preprocessing matters:** Wine required only scaling, while Churn needed a full `ColumnTransformer` + `Pipeline` to handle mixed feature types safely.
2. **Pipeline prevents data leakage:** fitting preprocessors inside a Pipeline ensures they see only training data during each CV fold.
3. **Metric choice depends on the task:** `f1_weighted` for multiclass Wine, `f1` for binary Churn with imbalance.
4. **Accuracy can be deceptive:** on Churn, a model predicting "No churn" always would already reach ~0.73 accuracy. F1 and Recall reveal the true quality.
5. **GridSearchCV gives stable estimates:** cross-validation averages over multiple splits, so the chosen hyperparameters generalize better than a single train/test split.
6. **Class imbalance must be addressed:** `stratify` in train/test split and `class_weight='balanced'` in models significantly improve minority-class Recall.