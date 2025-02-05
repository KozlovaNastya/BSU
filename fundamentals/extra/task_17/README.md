# Matrix Multiplication Program

This program performs matrix operations using statically allocated memory. It initializes two square matrices \( A \) and \( B \) with random values and multiplies them to generate a resultant matrix \( C \). The program allows the user to specify the matrix size and performs matrix multiplication accordingly.

## Features

- The program uses **statically allocated** memory for matrices \( A \), \( B \), and \( C \) with a maximum allowed size of **20\times20**.
- Matrix \( A \) and matrix \( B \) are **randomly initialized** with values between **0 and 99**.
- Matrix \( C \) is calculated as the product of matrices \( A \) and \( B \).
- The program outputs matrices \( A \), \( B \), and \( C \) to the console.

## Input and Output

### Input:
1. **Size of the Matrix (n)**: The user will be asked to input the size of the matrices (\( n \)), where \( 1 \leq n \leq 20 \).
2. **Number of Columns for Matrix B (k)**: The user will input the number of columns \( k \) for matrix \( B \), where \( 1 \leq k \leq 20 \).

### Output:
- The program prints matrices \( A \) and \( B \) after random initialization.
- The program prints the resultant matrix \( C \) after performing matrix multiplication.

### Example:

#### Input:
```
Enter size of matrix: 3
Enter number of columns for matrix B: 3
```

#### Output:
```
Matrix A:
12 45 67
34 89 23
56 78 90

Matrix B:
9 4 8
2 3 5
6 7 1

Resultant Matrix C:
582 625 721
983 823 1167
1416 1330 1668
```

### Explanation:
- **Matrix A** is filled with random values.
- **Matrix B** is also randomly filled.
- **Matrix C** is the result of matrix multiplication: \( C[i][j] = \sum A[i][l] \times B[l][j] \).

## Functions

### 1. `main()`:
- The main function handles:
  - Input of matrix size and column count for matrix \( B \).
  - Initialization of matrices \( A \) and \( B \) with random values.
  - Multiplication of matrices \( A \) and \( B \) to generate matrix \( C \).
  - Output of matrices \( A \), \( B \), and \( C \).

## Notes

- The matrix size \( n \) must be between **1 and 20** to prevent exceeding the fixed array size.
- The multiplication logic uses a nested loop approach to compute \( C[i][j] \).
- Random values are generated using `rand()`.
- The program assumes that the user enters valid integer inputs.
