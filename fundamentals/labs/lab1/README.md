# Taylor Series
## Program Description
This C++ program calculates the natural logarithm function using both a custom series expansion and the standard log() function, then compares their results.

## Functionality:
1. The user inputs
- `x` (must be in the range -1 < `x` < 1).
- `e` (precision threshold).
2. Computes `log((1 + x) / (1 - x))` using two approaches:
- `Function(e, x)`: A custom series expansion approximation.
- `Log1(x)`: Uses the standard `log()` function.
3. Outputs both values with 10 decimal places.
4. Displays the difference between the two values.

## Error Handling
- Ensures `x` is within the valid range (-1 < `x` < 1).
- Displays an error message for invalid input.

## Example Input
Enter x and limit
0.5 0.0001  

## Example Output
0.5493061443  
0.5493061443  
The sum of the own function differs from the sum of the standard function by
0.0000000000  
