# Exploratory data analysis

## Objective
Perform exploratory data analysis on two datasets with different feature types:
- **Anime Dataset** — mostly numerical features
- **Video Games Sales** — mixed features (numerical + categorical)

## Libraries Used
- `pandas`, `numpy` — data loading and processing
- `matplotlib`, `seaborn` — visualization
- `kagglehub` — dataset downloading

---

## 1. Data Loading

Datasets loaded from Kaggle:
- **Anime**: `CooperUnion/anime-recommendations-database`
- **Video Games Sales**: `gregorut/videogamesales`

---

## 2. Primary Data Audit

For each dataset:
- Preview of first and last rows (`.head()`, `.tail()`)
- Matrix dimensions (`.shape`)
- Data types and missing values (`.info()`)
- Type validation against actual values

---

## 3. Statistical Analysis and Cleaning

**Numerical features**: mean, median, std, quantiles via `.describe()`.

**Categorical features**: number of unique values and mode.

**Missing values**: detected and removed using `.dropna()`.

**Duplicates**: none found in either dataset.

**Special case — `genre` column (Anime)**: contains comma-separated combinations of genres, 
not single genres. Standard `.nunique()` returns 3264 — these are combinations. 
After splitting with `.str.split(', ').explode()`, the actual number of genres is about 43.

---

## 4. Visual Analysis: Anime

### Rating distribution
- **Histogram**: close to normal, peak around 6.5–7.5
- **KDE plot**: slight left skew (few low-rated anime)
- **Violin plot by type**: TV and Movie have narrower spread; ONA — wider

### Boxplot — outliers
- `rating` — few outliers (clean feature)
- `members` — many outliers (long right tail)
- `episodes` — many outliers (anime with hundreds of episodes)

**Conclusion**: rating is stable; members and episodes follow a power-law distribution.

---

## 5. Visual Analysis: Video Games Sales

### Year distribution
- Peak around 2005–2010
- Few games before 1995
- Different genres have different median release years

### Boxplot — outliers
- **All sales features** have many outliers (Pareto principle)
- `Global_Sales`: median ~0.17M, max ~82.74M (500× gap)
- `Year` — minor outliers only

**Conclusion**: sales follow a heavy-tailed distribution; a few blockbusters dominate the market.

---

## 6. Correlation Analysis: Anime

### Heatmap
- Strongest: `rating` ↔ `members` = **0.39** (moderate positive)
- `anime_id` ↔ `rating` = **−0.28** (weak negative)
- `anime_id` ↔ `members` = **−0.07** (no correlation)

### Scatterplot: rating vs members
- Weak positive trend: popular anime tend to have higher ratings
- Large spread — the relationship is non-linear

**Conclusion**: popularity partially predicts rating but not fully.

---

## 7. Correlation Analysis: Video Games Sales

### Heatmap
Very strong correlations:
- `NA_Sales` ↔ `Global_Sales` = **0.94**
- `EU_Sales` ↔ `Global_Sales` = **0.90**
- `Other_Sales` ↔ `Global_Sales` = **0.75**
- `JP_Sales` ↔ `Global_Sales` = **0.61**
- `NA_Sales` ↔ `EU_Sales` = **0.77**

Inverse correlation:
- `Rank` ↔ `Global_Sales` = **−0.43**

### Scatterplot: Other_Sales vs Global_Sales
Clear linear relationship — regional sales strongly predict global sales.

**Conclusion**: NA and EU are the largest markets; regional sales are tightly connected.

---

## 8. Final Conclusions

### Anime Dataset
- 12,294 records, 7 features (3 numerical, 4 categorical)
- One significant correlation: `rating` ↔ `members` (0.39)
- Many outliers in `members` and `episodes`
- Rating is nearly normally distributed
- `genre` column needs splitting to analyze individual genres

### Video Games Sales Dataset
- 16,598 records, 11 features (7 numerical, 4 categorical)
- Very strong correlations between regional and global sales (0.61–0.94)
- Heavy-tailed distributions in all sales features (Pareto principle)
- `Year` is weakly correlated with sales
- High potential for machine learning due to rich feature set

### Comparison
| Feature | Anime | Video Games |
|---------|-------|-------------|
| Records | 12,294 | 16,598 |
| Strong correlations | 1 | 6+ |
| Many outliers | members, episodes | all sales |
| Distribution shape | near-normal | heavily skewed |
| Ready for ML | medium | high |
