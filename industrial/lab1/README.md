# Numerical Computation of Sine Function

## Objective
To implement and analyze a numerical method for calculating the sine function using Taylor series expansion, comparing the precision and efficiency against the built-in `Math.sin()` function.

## Mathematical Foundation

### Taylor Series Expansion for Sine
The sine function can be approximated using its Taylor series expansion around 0:

``
sin(x) = x - x³/3! + x⁵/5! - x⁷/7! + ... + (-1)ⁿ * x²ⁿ⁺¹/(2n+1)!
``

### Recursive Formulation
The program uses a recursive formulation to compute terms efficiently:

``
termₙ₊₁ = termₙ × (-x²) / ((2n+1) × 2n)
``

where:
- Initial term: term₁ = x
- n = 1, 2, 3, ...

## Program Structure

### Input Parameters
``java myFirstClass <x> <k>``
- **x**: Value (in radians) for which to compute sin(x)
- **k**: Number of decimal places for precision (Eps = 10⁻⁽ᵏ⁺¹⁾)

### Validation Logic
1. Exactly 2 command-line arguments required
2. k must be `> 1` (ensures reasonable precision)

### Algorithm Implementation
```java
double Eps = 1 / Math.pow(10, k + 1);
double result = 0;
double step = x;  // First term: x
int n = 1;

while (Math.abs(step) >= Eps) {
    result += step;
    step = (-1) * (step * x * x) / ((2 * n + 1) * 2 * n);
    n++;
}
```

### Output Format
- Both computed value and Math.sin(x) printed with k decimal places
- Uses printf with dynamic format string: `"%." + args[1] + "f\n"`

### Key Features
1. Efficient Computation
- Reuses previous term to compute next term: O(1) per iteration
- Avoids recomputing factorials and powers from scratch

2. Precision Control
- Stop criterion: `|termₙ| < 10⁻⁽ᵏ⁺¹⁾`
- Provides k decimal places of accuracy in final result

3. Error Handling
- Validates input arguments
- Ensures `k > 1` for meaningful precision
- Clear error messages and proper exit codes
