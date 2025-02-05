# Matrix Operations Program

This program performs matrix operations using dynamically allocated memory. It initializes a square matrix with random values, computes its trace (sum of diagonal elements), and calculates the sum of the upper left triangular portion.

## Features

- The program dynamically allocates memory for a square matrix \( A \).
- The matrix is filled with random values ranging from 0 to 99.
- It calculates:
  - **Trace of the matrix**: The sum of its diagonal elements.
  - **Sum of the upper left triangular part**: The sum of all elements located in the upper left triangle (including the main diagonal).
- Proper memory deallocation is performed at the end to free up allocated space.

## Input and Output

### Input:
1. **Size of the Matrix**: The user is prompted to enter the size of the square matrix (\( n \)), where \( 1 \leq n \leq 10 \).

### Output:
- The program displays the randomly generated matrix.
- It then prints the computed trace and the sum of the upper left triangle.

### Example:

#### Input:
Enter the size: 3

#### Output:
Generated matrix:  
41 67 34  
0  69 24  
78 58 62
Trace of the matrix: 172  
Sum of the upper left triangle = 211

### Explanation:
- A 3×3 matrix is randomly generated.
- The **trace** is computed as \( 41 + 69 + 62 = 172 \).
- The **sum of the upper left triangle** includes elements above and on the diagonal:
  41 67 34 0 69 78
  The sum of these elements is **211**.

## Functions

### 1. `main()`:
- Handles user input for the matrix size.
- Dynamically allocates memory for the matrix.
- Fills the matrix with random values.
- Computes the trace and upper left triangle sum.
- Displays the results.
- Deallocates memory to prevent memory leaks.

## Notes

- The matrix size (\( n \)) must be a positive integer between 1 and 10.
- The program assumes valid user input (integer for matrix size).
- After the program completes, all allocated memory is properly freed.
