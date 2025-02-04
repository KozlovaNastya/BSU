# Matrix Addition Program

This program performs matrix operations using dynamically allocated memory. It initializes two triangular matrices \( A \) and \( B \) based on user input, then adds them to generate a resultant matrix \( C \). The program uses dynamic memory allocation to create and manage the matrices.

## Features

- The program dynamically allocates memory for three matrices: \( A \), \( B \), and \( C \).
- Matrix \( A \) is a lower triangular matrix (only the lower triangle of the matrix is filled with values).
- Matrix \( B \) is an upper triangular matrix (only the upper triangle of the matrix is filled with values).
- Matrix \( C \) is initialized as a zero matrix, then filled by adding matrices \( A \) and \( B \).
- Proper memory deallocation is performed at the end to free up allocated space.

## Input and Output

### Input:
1. **Size of the Matrix**: The user will be asked to input the size of the matrix (\( n \)) where \( 1 \leq n \leq 10 \).

### Output:
- The program displays the initialized matrices \( A \), \( B \), and the resultant matrix \( C \) after adding matrices \( A \) and \( B \).

### Example:

#### Input:
Enter the size: 3

#### Output:
Initialized triangular matrix A: 1 2 2 3 3 3  
Initialized triangular matrix B: 3 3 3 2 2 1  
Resultant matrix after A and B addition: 4 3 3 4 4 3 3 3 3

### Explanation:
- Matrix A is a lower triangular matrix filled with values as follows:  
1 2 2 3 3 3
- Matrix B is an upper triangular matrix filled with values as follows:  
3 3 3 2 2 1
- After adding \( A \) and \( B \), the resultant matrix \( C \) is displayed.

## Functions

### 1. `main()`:
 - The main function handles:
   - Input of the matrix size.
   - Dynamic memory allocation for matrices \( A \), \( B \), and \( C \).
   - Initialization of matrices \( A \) and \( B \) as triangular matrices.
   - Addition of matrices \( A \) and \( B \) into the resultant matrix \( C \).
   - Deallocation of memory to prevent memory leaks.

## Notes

- The matrix size (\( n \)) must be a positive integer between 1 and 10.
- The program assumes that the user enters valid input (e.g., an integer for matrix size).
- After the program completes, all allocated memory is properly deallocated to avoid memory leaks.
