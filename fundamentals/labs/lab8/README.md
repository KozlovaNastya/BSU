# Ordinary Fractions

## Program Description
This program implements a Fraction class in C++, allowing various arithmetic operations, comparisons, and conversions between fractions. It also includes exception handling for division by zero errors and demonstrates the use of several overloaded operators.

## Features
1. Fraction Operations:
- Supports addition, subtraction, multiplication, division of fractions.
2. Compound Assignment:
- Includes +=, -=, *=, /= for operations involving fractions and integers.
3. Unary Operations:
- Supports unary negation and reciprocal of fractions.
4. omparison Operators:
- Fractions can be compared using ==, <=, <, >=, >.
5. Input and Output:
- Overloaded << and >> operators for user-friendly input/output of fractions.
6. Exception Handling:
- Custom exception DivByZeroException is thrown when attempting to divide by zero.

## Files
1. Fraction.h
- Header file containing the definition of the Fraction class, the DivByZeroException class, and function prototypes.
2. Fraction.cpp
- Contains the implementation of the Fraction class methods and operators.
3. main.cpp
- The main program that demonstrates the functionality of the Fraction class. It generates random fractions, performs arithmetic operations, and allows the user to input fractions and perform various operations.

## How It Works
1. Random Fractions:
- The program generates a set of random fractions, some of which are derived from previous fractions (e.g., the product of numerators and denominators).
2. User Input:
- The user is prompted to input two fractions, and the program will perform arithmetic operations on them.
3. Arithmetic Operations:
- The program supports addition, subtraction, multiplication, and division for both fractions and integers.
- It also supports unary operations like negation (-) and reciprocal (!).
4. Comparison Operations:
- Fractions can be compared using operators like ==, <, >, <=, and >=.
5. Exception Handling:
- If the user tries to divide by zero, an exception will be thrown, and the error message will be displayed.

## Example Input
Enter fractions as follows: 1/3  
Enter drob1: 2/5  
Enter drob2: 3/4  

## Example Output
Add drob1 + drob2:  
23/20  
Subtract drob1 - drob2:  
-7/20  
Multiply drob1 * drob2:  
6/20  
Divide drob1 / drob2:  
8/15  
Unary minus for drob1:  
-2/5  
Reverse drob1:  
5/2  
Operation += with number 3 and drob2:  
14/4

## Error Handling
- Division by Zero:
  - If you try to divide a fraction by zero or enter a fraction with a denominator of zero, a DivByZeroException will be thrown, and an error message will be printed.

## Notes
- The program will automatically simplify fractions (e.g., 2/4 becomes 1/2).
- The program supports both integer and fraction types for arithmetic operations, making it versatile for various calculations.
