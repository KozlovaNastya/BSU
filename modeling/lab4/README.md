# Population Dynamics Models
## Numerical Analysis of Dynamical Systems

### Core Models Analyzed
1. **Exponential Model**: `x_{n+1} = r × x_n`
2. **Logistic Model**: `x_{n+1} = r × x_n × (1 - x_n)`  
3. **Moran Model**: `x_{n+1} = x_n × exp(r × (1 - x_n))`
4. **Host-Parasite Model**: 
   - Hosts: `H_{n+1} = b × H_n × exp(-a × P_n)`
   - Parasites: `P_{n+1} = c × H_n × (1 - exp(-a × P_n))`

### Key Parameter Ranges
- **Exponential**: r ∈ [0.5, 2.0]
- **Logistic**: r ∈ [2.0, 4.0]  
- **Moran**: r ∈ [1.5, 3.0]
- **Host-Parasite**: a ∈ [0.05, 0.3], b ∈ [1.2, 2.5], c ∈ [0.5, 2.0]

## Critical Numerical Findings

### 1. Exponential Model
| r | Behavior | Key Value | Initial Condition Impact |
|---|----------|-----------|--------------------------|
| 0.5 | Extinction | Final = 0 | All x₀ → extinction |
| 1.0 | Stable equilibrium | Final = x₀ | Perfect stability |
| 1.5 | Uncontrolled growth | >10¹⁰⁰ | Exponential explosion |
| 2.0 | Uncontrolled growth | >10¹⁵⁰ | Extreme divergence |

**Conclusion**: Bifurcation at r=1.0. For r<1: extinction; r=1: neutral; r>1: explosive growth.

### 2. Logistic Model - Bifurcation Points
| r | Regime | Fixed Points | Characteristic |
|---|---------|--------------|----------------|
| 2.0 | Stable | 0.5000 | Single stable point |
| 2.8 | Stable | 0.6429 | Higher equilibrium |
| 3.2 | Periodic | ~0.7995/0.5130 | Period-2 oscillations |
| 3.5 | Chaotic | Varies widely | Sensitive to x₀ |
| 3.8 | Chaotic | Highly variable | Strong chaos |
| 4.0 | Chaotic/Extinct | 0 or chaotic | Boundary behavior |

**Key Observations**:
- Chaos emerges around r ≈ 3.57
- x₀ > 1 leads to extinction
- Period doubling route to chaos

### 3. Moran Model Stability
| r | Behavior | Mean Value | Stability |
|---|----------|------------|-----------|
| 1.5 | Stable equilibrium | 1.0000 | Very stable |
| 2.0 | Weak oscillations | ~1.0000 | Mild fluctuations |
| 2.5 | Chaotic oscillations | Varies | Strong chaos |
| 3.0 | Highly chaotic | Widely varying | Extreme sensitivity |

**Insight**: Moran model shows similar bifurcation to logistic but at different r values.

### 4. Host-Parasite Critical Parameters

#### Parameter a (Infection Efficiency):
- **a < 0.03**: Host extinction
- **0.03 < a < 0.48**: Parasite extinction  
- **a > 0.48**: Return to host extinction

#### Parameter c (Parasite Reproduction):
- **c < 0.218**: Host extinction
- **c > 0.218**: Parasite extinction

#### Parameter b (Host Reproduction):
- No critical transitions in tested range
- Always leads to parasite extinction

**Surprising Result**: Coexistence was never observed in tested parameter ranges. Model consistently leads to extinction of one species.

## Comparative Analysis

### Model Sensitivity Ranking:
1. **Logistic**: Most sensitive to r, shows full range of dynamics
2. **Moran**: Moderate sensitivity, chaotic at lower r
3. **Exponential**: Simple bifurcation at r=1
4. **Host-Parasite**: Complex but tends to extinction

### Numerical Stability:
- **Exponential**: Numerically unstable for r>1 (overflow)
- **Logistic**: Well-behaved but chaotic
- **Moran**: Stable numerically even in chaos
- **Host-Parasite**: Prone to numerical overflow

## Key Conclusions

### 1. Universality of Chaotic Behavior
Both logistic and Moran models exhibit:
- Period doubling bifurcations
- Route to chaos via increasing r
- Sensitive dependence on initial conditions
- Emergence of complex dynamics from simple equations

### 2. Parameter Space Exploration
Critical finding: **Most parameter combinations lead to extinction** in host-parasite model, suggesting the model may need adjustment for realistic ecological scenarios.

### 3. Initial Condition Dependence
- **Exponential**: Memoryless - final state independent of x₀ magnitude
- **Logistic**: Highly sensitive - different attractors for different x₀
- **Moran**: Moderate sensitivity
- **Host-Parasite**: Scale-dependent but pattern consistent

### 4. Numerical Implementation Insights
- Need for careful handling of extreme values
- Importance of sufficient simulation steps (≥200)
- Classification algorithms work well for distinguishing regimes

### 5. Ecological Implications
- Simple population models can exhibit complex dynamics
- Chaos is common in biological systems
- Parameter tuning critical for model realism
- Extinction often more likely than stable coexistence

## Limitations and Future Work
1. **Numerical precision**: Extreme values cause overflow
2. **Parameter ranges**: Limited exploration of host-parasite coexistence
3. **Model comparison**: Direct quantitative comparison challenging due to different scales
4. **Real-world validation**: Need empirical parameter estimation

**Overall Insight**: Simple deterministic models can produce remarkably complex behavior, mirroring the richness of natural ecological systems despite mathematical simplicity.
