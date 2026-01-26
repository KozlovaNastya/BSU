# Coin Toss Simulation

## Objective
To investigate statistical characteristics of coin toss sequences with different probabilities of getting heads.

## Methodology
- Simulation of 100 coin tosses with a given probability of heads `p`
- Conducting 10,000 experiments for each `p` value
- Analysis of average number of heads, 95% confidence interval, and streak patterns

## Implementation
### Core Functions
1. `coin_toss(p)` - single coin toss
2. `model(p)` - 100 coin tosses
3. `find_max_series(sequence)` - finds the maximum streak of heads

### Investigated Parameters
- Probability of heads `p` ranging from 0.05 to 0.95 with step 0.05
- For each `p`, the following were calculated:
  - Average number of heads
  - Width of 95% confidence interval
  - Probability of getting a streak of 5 or more heads
  - Average length of maximum streak

## Key Results
### For p = 0.5 (Fair Coin)
- Average number of heads: 50.00
- Probability of getting >60 heads: 0.0176 (1.76%)
- 95% confidence interval: [40.0, 60.0] (width: 20.0)
- Probability of at least one streak of 5 heads: 0.5968 (59.68%)

### Distribution Analysis for p = 0.5
Most outcomes (95.2%) fall between 40 and 60 heads:
- [30, 40): 1.98%
- [40, 50): 44.91%
- [50, 60): 50.33%
- [60, 70): 2.78%

## Dependencies
The relationships between probability `p` and various statistics show expected patterns:
1. **Average heads vs p**: Linear relationship (average = 100 × p)
2. **Confidence interval width vs p**: Symmetric curve with maximum at p = 0.5
3. **Streak probability vs p**: Increases with p, reaching near certainty for p > 0.7
4. **Average max streak vs p**: Increases with p, from ~1 at p=0.05 to ~20 at p=0.95

## Visualization
Four plots were generated showing the relationships between:
1. Average number of heads and probability p
2. 95% confidence interval width and probability p
3. Probability of 5-head streak and probability p
4. Average maximum streak length and probability p

## Conclusion
The simulation demonstrates fundamental probability principles:
- The average outcome follows theoretical expectations
- Variability is greatest for fair coins (p = 0.5)
- Streak probabilities increase non-linearly with p
- The Central Limit Theorem is evident in the distribution of results

## Tools Used
- Python with NumPy and Matplotlib
- Monte Carlo simulation with 10,000 trials
- Statistical analysis including percentiles and means
