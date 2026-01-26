#Game Theory Strategy Analysis

## Objective
To analyze and compare different strategies in a two-player game using point-based payoff matrices and evaluate their effectiveness through pairwise competition.

## Game Rules
- Two players choose 0 or 1 each round
- Payoff matrix:
  - Player A chooses row, Player B chooses column
  - Matrix: [[3, 0], [5, 1]]
  - Interpretation: Higher values are better

## Strategies Analyzed

### 1. Alex
**Strategy**: Always cooperate (always choose 1)

### 2. Bob  
**Strategy**: Always defect (always choose 0)

### 3. Clara
**Strategy**: Tit-for-Tat (start with 1, then copy opponent's last move)

### 4. Denis
**Strategy**: Anti-Tit-for-Tat (start with 1, then choose opposite of opponent's last move)

### 5. Emma
**Strategy**: Periodic betrayal (cooperate except every 20th round)

### 6. Frida
**Strategy**: Conditional cooperation (cooperate if opponent always cooperates, else defect)

### 7. George
**Strategy**: Forgiveness strategy (defect initially, then copy opponent unless they defect too much)

## Methodology
- Each strategy plays against every other strategy (including itself)
- 200 rounds per matchup
- Two metrics tracked:
  1. **Total points**: Sum of points earned across all rounds
  2. **Dominant series**: Longest consecutive streak where one player scores 5 and opponent scores 0

## Results

### Table 1: Total Points Matrix
| vs →     | alex | bob  | clara | denis | emma | frida | george | **Total** |
|----------|------|------|-------|-------|------|-------|--------|-----------|
| **alex** | 200  | 1000 | 200   | 996   | 240  | 200   | 280    | **6232**  |
| **bob**  | 0    | 600  | 597   | 0     | 30   | 597   | 600    | **4848**  |
| **clara**| 200  | 602  | 200   | 450   | 231  | 200   | 593    | **4952**  |
| **denis**| 1    | 1000 | 450   | 400   | 40   | 989   | 474    | **6708**  |
| **emma** | 190  | 980  | 226   | 940   | 220  | 901   | 305    | **7524**  |
| **frida**| 200  | 602  | 200   | 9     | 51   | 200   | 599    | **3722**  |
| **george**| 180  | 600  | 588   | 419   | 210  | 599   | 600    | **6392**  |

### Table 2: Longest Dominant Series Matrix
| vs →     | alex | bob | clara | denis | emma | frida | george | **Total** |
|----------|------|-----|-------|-------|------|-------|--------|-----------|
| **alex** | 0    | 200 | 0     | 199   | 1    | 0     | 1      | **802**   |
| **bob**  | 0    | 0   | 0     | 0     | 0    | 0     | 0      | **0**     |
| **clara**| 0    | 1   | 0     | 1     | 1    | 0     | 1      | **8**     |
| **denis**| 0    | 200 | 1     | 0     | 0    | 197   | 1      | **798**   |
| **emma** | 0    | 19  | 1     | 18    | 0    | 19    | 2      | **118**   |
| **frida**| 0    | 1   | 0     | 1     | 1    | 0     | 1      | **8**     |
| **george**| 0   | 0   | 1     | 1     | 1    | 1     | 0      | **8**     |

## Rankings

### By Total Points
1. **emma** (7524 points) - Periodic betrayal performs best overall
2. **denis** (6708 points) - Anti-Tit-for-Tat is second best
3. **george** (6392 points) - Forgiveness strategy ranks third
4. **alex** (6232 points) - Always cooperate ranks fourth
5. **clara** (4952 points) - Tit-for-Tat ranks fifth
6. **bob** (4848 points) - Always defect ranks sixth  
7. **frida** (3722 points) - Conditional cooperation performs worst

### By Dominant Series
1. **alex** (802 series) - Always cooperate creates most exploitation opportunities
2. **denis** (798 series) - Anti-Tit-for-Tat also creates many dominant series
3. **emma** (118 series) - Periodic betrayal creates moderate exploitation
4. **clara, frida, george** (8 series each) - Balanced strategies create few dominant series
5. **bob** (0 series) - Always defect cannot create dominant series

## Key Insights

1. **Periodic betrayal (emma)** is the most successful overall strategy, balancing cooperation with occasional exploitation.

2. **Always cooperate (alex)** is highly exploitable, creating the most dominant series for opponents but still scoring well overall.

3. **Always defect (bob)** performs poorly overall and cannot create dominant series.

4. **Anti-Tit-for-Tat (denis)** is effective at exploiting cooperative opponents while protecting against exploitation.

5. **Balanced strategies** (clara, frida, george) create fairness but don't maximize points.

6. The game rewards **strategic unpredictability** combined with occasional exploitation of cooperative opponents.

## Conclusion
The most successful strategies in this game are those that:
- Occasionally exploit overly cooperative opponents
- Maintain some level of cooperation for mutual benefit
- Adapt to opponent behavior

The results demonstrate fundamental game theory principles: purely cooperative strategies are exploitable, purely selfish strategies perform poorly, and balanced adaptive strategies yield the best results in repeated interactions.
