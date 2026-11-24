# Dimensionality Reduction

A study of linear and non-linear dimensionality reduction techniques — **PCA**, **t-SNE**, and **UMAP** — applied to two high-dimensional datasets. The lab also validates how compression affects downstream model quality and training time.

## Datasets

| Dataset | Source | Shape | Task | Target |
|---|---|---|---|---|
| **High Dimensional Datascape** | [Kaggle](https://www.kaggle.com/datasets/krishd123/high-dimensional-datascape) | 230 × 537 | Classification | `Label` (binary) |
| **Used Car Prices** | [Kaggle](https://www.kaggle.com/datasets/krishnaharish1/used-car-prices-synthetic-benchmark) | 25 000 × 10 | Regression | `price_usd` |

Both datasets are **new** relative to previous labs (Wine and Telco Churn are not reused).

## Methods

- **PCA** (linear) — with cumulative explained variance curve to choose 85% / 95% thresholds.
- **t-SNE** (non-linear) — swept `perplexity` over {5, 15, 30, 50}.
- **UMAP** (non-linear, `umap-learn`) — swept `n_neighbors` over {5, 15, 30, 50}.
- **Validation** — Logistic Regression (High Dim) and Gradient Boosting (Used Car), trained before and after PCA, compared on quality and time.

## Results

### PCA compression (High Dim, 536 features)

| Information kept | Components needed | % of original |
|---|---|---|
| 85% variance | **22** | 4.1% |
| 95% variance | **31** | 5.8% |

2D projection explains only **13.2%** of the variance — expected for `p > n` data.

### Visualization comparison (High Dim)

| Method | Speed | Class separation |
|---|---|---|
| PCA (2D) | **~0.01 s** | Weak |
| t-SNE (perplexity=15) | 1.2 s | Local micro-clusters only |
| UMAP (n_neighbors=15) | **0.5 s** | Local structure, faster than t-SNE |

None of the methods separated the binary labels — the data has no low-dimensional linear or locally non-linear boundary between classes.

### Validation: before vs after PCA

| Task | Model | Metric | Before PCA | After PCA | Δ |
|---|---|---|---|---|---|
| High Dim | LogisticRegression | F1 | **0.9565** | 0.8857 | −7.08 pp |
| High Dim | LogisticRegression | Time | 0.0506 s | **0.0123 s** | **−75.7%** |
| Used Car | GradientBoosting | R² | **0.9524** | 0.9399 | −1.25 pp |
| Used Car | GradientBoosting | Time | **4.24 s** | 24.89 s | **+487%** |

## Key Findings

1. **PCA is a friend of linear models, an enemy of trees.**
   - Logistic Regression sped up **4×** after PCA.
   - Gradient Boosting slowed down **6×** after PCA: trees build axis-aligned splits, and PCA mixes axes into linear combinations — forcing deeper, slower trees.
2. **Quality drops in both cases, but modestly.** F1 lost 7 pp; R² lost only 1.25 pp. For regression on a small feature set, PCA costs almost nothing in quality but hurts time.
3. **No method separated the binary classes in 2D.** t-SNE and UMAP produce nice pictures but they reveal *local* neighborhoods, not label boundaries. The class structure is non-linear and high-dimensional.
4. **UMAP is 2–3× faster than t-SNE** and preserves global structure better. For interactive visualization, UMAP is the preferred choice.
5. **Dimensionality reduction is a trade-off, not a free lunch.** Use PCA to speed up *linear* pipelines; avoid it for tree-based ensembles. For visualization, use UMAP.

## Visual Summary

The final chart compares training time and quality before vs after PCA:

- **Time:** −76% (LogReg, High Dim) vs +487% (GBR, Used Car).
- **Quality:** −7.08 pp (F1) vs −1.25 pp (R²).

One glance explains the whole lab: PCA is model-dependent.

## Stack

`pandas` · `numpy` · `scikit-learn` · `scipy` · `umap-learn` · `matplotlib` · `seaborn` · `kagglehub`
