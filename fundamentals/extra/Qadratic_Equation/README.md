# Quadratic Equation Solver  

## Program Description  
This C++ program solves a quadratic equation of the form `ax² + bx + c = 0` by calculating its roots using the quadratic formula.  

## Functionality  
1. Prompts the user to enter coefficients `a`, `b`, and `c`.  
2. Computes the discriminant `D = b² - 4ac`.  
3. Determines the number of real solutions based on the value of `D`:  
   - If `D > 0`, computes and prints two distinct real roots.  
   - If `D = 0`, computes and prints one real root (a double root).  
   - If `D < 0`, prints `"no solutions"`, as the roots are complex.  

## Error Handling  
- Ensures the input is valid for calculations.  
- Accounts for cases where the equation has no real solutions.  

## Example input  
Enter a  
1  
Enter b  
-3  
Enter c  
2

## Example output  
x1 = 2  
x2 = 1
