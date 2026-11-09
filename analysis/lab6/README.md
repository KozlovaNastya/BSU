# Clustering Analysis: Wine Quality & Telco Customer Churn

A comparative study of unsupervised learning algorithms on two datasets: **Wine Quality** (physicochemical properties) and **Telco Customer Churn** (customer behavior). The objective is to evaluate how different clustering algorithms perform on continuous vs. high-dimensional categorical data.

## Datasets

| Dataset | Source | Samples | Features used | Target removed |
|---|---|---|---|---|
| **Wine** | [Kaggle](https://www.kaggle.com/datasets/yasserh/wine-quality-dataset) | 1143 | 11 (chemical) | `quality`, `Id` |
| **Churn** | [Kaggle](https://www.kaggle.com/datasets/blastchar/telco-customer-churn) | 7043 | 4 numeric + 15 categorical | `customerID`, `Churn` |

**Preprocessing:** `StandardScaler` for numeric features; `SimpleImputer` + `OneHotEncoder` for categorical (via `ColumnTransformer` and `Pipeline`).

## Methods

- **K-Means** with the Elbow Method (inertia) and Silhouette Score.
- **DBSCAN** with K-distance graph for `eps` selection and a manual parameter sweep.
- **Agglomerative Clustering** (Ward linkage) with dendrograms.
- **PCA** (2 components) for visualization.

## Results Summary

| Dataset | Algorithm | Params | Clusters | Noise | Silhouette |
|---|---|---|---|---|---|
| Wine | K-Means | k=7 | 7 | 0 | **0.1955** |
| Wine | DBSCAN | eps=2.5, min=5 | 2 | 55 (4.8%) | — |
| Wine | Agglomerative | k=7 | 7 | 0 | 0.1460 |
| Churn | K-Means | k=3 | 3 | 0 | **0.2621** |
| Churn | DBSCAN | eps=2.0, min=5 | 4 | 29 (0.4%) | — |
| Churn | Agglomerative | k=3 | 3 | 0 | 0.2194 |

## Key Findings

- **K-Means performed best** on both datasets (highest silhouette, fastest, reproducible).
- **Dendrograms revealed** that Wine has a natural 2–3 cluster structure — `k=7` from the elbow method is an artifact of inertia, not real separation.
- **DBSCAN failed on Wine** (no density-based structure: either everything is noise or everything merges). It worked well on Churn (4 clusters, 0.4% noise).
- **Low silhouette scores (0.15–0.26) are expected** here: Wine is a continuous quality spectrum, and Churn suffers from the curse of dimensionality after one-hot encoding.

## Cluster Interpretation

**Churn (k=3)** — three customer segments:
- *Loyal Premium* (32%) — long tenure, high spend, low churn risk.
- *Budget, No Internet* (22%) — low value, medium risk.
- *New At-Risk* (46%) — short tenure, month-to-month contracts, electronic check payments → **primary target for retention campaigns**.

**Wine (k=7)** — chemical profiles:
- Clusters differentiated by `volatile acidity` (defects), `residual sugar` (sweetness), `alcohol`, and `sulphates` (anomalies).
- Isolated rare clusters: 19-point sulfate anomaly, 31-point high-sugar group.
