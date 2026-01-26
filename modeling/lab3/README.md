# Advanced Game Theory Strategy Analysis

## Objective
To analyze and compare 14 different strategies in a two-player game using statistical methods, evaluating their effectiveness through pairwise competition with multiple metrics.

## Game Rules
- Two players choose 0 or 1 each round
- Payoff matrix: [[3, 0], [5, 1]]
- Higher values are better for each player
- Games consist of 200 rounds (or 100 repeated games for stochastic strategies)

## Extended Strategy Set

### Original Strategies (Deterministic)
1. **Alex**: Always cooperate (always choose 1)
2. **Bob**: Always defect (always choose 0)
3. **Clara**: Tit-for-Tat (start with 1, copy opponent's last move)
4. **Denis**: Anti-Tit-for-Tat (start with 1, choose opposite of opponent)
5. **Emma**: Periodic betrayal (cooperate, defect every 20th round)
6. **Frida**: Conditional cooperation (cooperate if opponent always cooperates)
7. **George**: Forgiveness strategy (defect initially, copy opponent unless too many defects)

### New Stochastic Strategies
8. **Hank**: Random 50/50 (choose randomly with equal probability)
9. **Ivan**: Mostly cooperate (90% cooperate, 10% defect)
10. **Jack**: Triggered random (defect initially, 75% cooperate after opponent cooperates)
11. **Kevin**: Mostly copy (75% copy opponent, 25% do opposite)
12. **Lucas**: Periodic cooperation (defect for random period, then cooperate once)
13. **Maxx**: Alternating pattern (switch between 0 and 1 at random intervals)
14. **Natan**: Emotional strategy (track goodwill/anger, defect probabilistically based on emotions)

## Methodology
- **Deterministic strategies**: Play 1 game of 200 rounds
- **Stochastic strategies**: Play 100 games of 200 rounds each, take averages
- Each strategy plays against every other strategy (including itself)
- **Metrics tracked**:
  1. **Total points**: Sum of points earned
  2. **Dominant series**: Longest streak where player scores 5 and opponent scores 0
  3. **Median**: Middle value of scores across repetitions
  4. **Mode**: Most common score value
  5. **Variance**: Measure of score variability

## Statistical Functions

### Mode Calculation
Custom `mode()` function handles continuous data by:
1. Determining optimal number of bins using `k = log₂(1 + n)`
2. Creating equal-width intervals across data range
3. Finding interval with highest frequency
4. Returning average value within that interval

### Game Simulation
- `play_game()`: Single 200-round game for deterministic strategies
- `play_game_st()`: 100 repeated games for stochastic strategies

## Results

### Overall Performance Rankings

#### By Total Points (All Strategies)
1. **emma** (14174 points) - Periodic betrayal
2. **ivan** (14067 points) - Mostly cooperate (90%)
3. **denis** (12963 points) - Anti-Tit-for-Tat
4. **george** (12875 points) - Forgiveness strategy
5. **natan** (12871 points) - Emotional strategy
6. **alex** (12823 points) - Always cooperate
7. **hank** (12709 points) - Random 50/50
8. **kevin** (12648 points) - Mostly copy (75%)
9. **jack** (12532 points) - Triggered random
10. **maxx** (12368 points) - Alternating pattern
11. **lucas** (11857 points) - Periodic cooperation
12. **clara** (11552 points) - Tit-for-Tat
13. **bob** (10334 points) - Always defect
14. **frida** (9216 points) - Conditional cooperation

#### By Dominant Series Creation
1. **alex** (880 series) - Always cooperate creates most exploitation opportunities
2. **denis** (872 series) - Anti-Tit-for-Tat exploits cooperators effectively
3. **ivan** (279 series) - Mostly cooperate still gets exploited frequently
4. **emma** (196 series) - Periodic betrayal creates moderate exploitation
5. **lucas** (168 series) - Periodic cooperation vulnerable to exploitation
6. **maxx** (104 series) - Alternating pattern somewhat vulnerable
7. **hank** (93 series) - Random strategy occasionally exploited
8. **bob** (0 series) - Always defect cannot create dominant series

## Key Statistical Insights

### 1. Performance Variability
- **Deterministic strategies** (alex, bob, clara, etc.) show zero variance against each other
- **Stochastic strategies** show significant variance, especially:
  - **lucas**: Highest variance (up to 16283.22) due to random period lengths
  - **maxx**: Moderate variance from alternating patterns
  - **kevin**: Low to moderate variance from mostly-copy behavior

### 2. Median vs Mean Analysis
- For most strategies, median and mean scores are similar
- Exceptions occur with highly skewed distributions (e.g., lucas vs alex: median 33 vs mean 66)
- This indicates occasional extreme outcomes rather than consistent performance

### 3. Mode Analysis
- **Deterministic strategies**: Mode equals actual score (no variation)
- **Stochastic strategies**: Mode often close to mean, indicating central tendency
- Some strategies (lucas, maxx) show modes significantly different from means, indicating multi-modal distributions

### 4. Strategy Effectiveness Spectrum

#### Top Performers:
- **Emma (Periodic betrayal)**: Best overall score by balancing cooperation with strategic exploitation
- **Ivan (Mostly cooperate)**: High scores by maintaining cooperation while occasionally defecting
- **Denis (Anti-Tit-for-Tat)**: Excellent at exploiting cooperative opponents

#### Middle Performers:
- **George, Natan, Alex**: Adaptive strategies that perform reasonably well
- **Hank, Kevin, Jack**: Stochastic strategies with moderate success

#### Bottom Performers:
- **Clara (Tit-for-Tat)**: Surprisingly low ranking despite theoretical appeal
- **Bob (Always defect)**: Poor performance due to lack of cooperation
- **Frida (Conditional cooperation)**: Worst performer, too rigid in defection

## Strategic Insights

### 1. The Exploitation Trade-off
Strategies that create many dominant series (alex, denis) tend to have high total scores when playing against exploitable opponents but may suffer against retaliatory strategies.

### 2. Stochastic Advantage
Introducing randomness (hank, ivan, kevin) generally improves performance over purely deterministic strategies, making behavior less predictable and harder to exploit.

### 3. Adaptation vs Consistency
The most successful strategies (emma, ivan) balance:
- **Consistency** enough to build cooperation
- **Adaptation** to opponent behavior
- **Strategic unpredictability** to avoid exploitation

### 4. Emotional/Complex Strategies
**Natan** (emotional strategy) performs surprisingly well (5th place), suggesting that tracking opponent behavior with "memory" of interactions can be effective.

## Conclusion

1. **No single dominant strategy** exists; success depends on opponent mix
2. **Periodic betrayal (emma)** is most robust across diverse opponents
3. **Introducing randomness** improves performance against adaptive opponents
4. **Pure strategies** (always cooperate/defect) are exploitable
5. **Complex adaptive strategies** with memory (george, natan) perform well but require more implementation complexity

The analysis demonstrates that in repeated game scenarios:
- **Moderate cooperation with occasional defection** yields best results
- **Predictability is costly** - strategies must be somewhat unpredictable
- **Adaptation to opponent behavior** is crucial for long-term success
- **Statistical analysis** (beyond simple averages) reveals important strategic properties

## Technical Implementation Notes
- Custom mode calculation handles continuous score distributions
- Separate treatment of deterministic vs stochastic strategies
- Comprehensive metrics: mean, median, mode, variance, dominant series
- Scalable design allowing easy addition of new strategies
