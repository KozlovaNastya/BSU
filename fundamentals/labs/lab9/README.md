# Class Matrix

## Program Description
This program demonstrates basic matrix operations such as addition, subtraction, multiplication, division, and checking for symmetry. It utilizes dynamic memory allocation to store matrix data and performs various operations on matrices. The program allows the user to interact with matrices by inputting their elements, and it generates random matrices as well.

## Features
1. Matrix Operations:
- Addition (+)
- Subtraction (-)
- Scalar multiplication and division (*, /)
- Matrix multiplication
- Comparison (==)
2. Symmetry Check:
  - Check if a matrix is symmetric.
3. Random Matrix Generation:
- Generate random matrices with specified dimensions and values.
4. Matrix Input:
- Manually input matrix values.
5. Memory Management:
- Dynamic allocation and deallocation of memory for matrix storage.

## Files
1. `main.cpp`
- The entry point of the program that demonstrates matrix operations, including matrix input, generation of random matrices, and various matrix arithmetic operations.
2. `matrix.h`
- Header file containing the declaration of the matrix class, which includes the member functions for matrix operations and the necessary overloads for operators.
3. `matrix.cpp`
- Implementation of the matrix class methods. Contains the logic for memory allocation, copying values between matrices, matrix operations, and the implementation of various operator overloads.

## How It Works
1. Matrix Initialization:
- Matrices are initialized with specific values or can be filled with random values. Matrices can also be manually input by the user.
2. Matrix Operations:
- The program supports basic arithmetic operations such as addition, subtraction, multiplication, and division (both by a scalar and matrix). It also supports matrix multiplication and comparison (==).
3. Symmetry Check:
- The program checks if a matrix is symmetric by comparing its elements across the diagonal.
4. Memory Management:
- The program ensures proper memory allocation and deallocation for matrices to avoid memory leaks.

## Example Input
Enter the number of rows and columns for matrix D (rows must match B): 4 5  
Enter row 1: 1 2 3 4 5  
Enter row 2: 6 7 8 9 10  
...

## Example Output
matrix A:  
-2 -1 0 1 2   
-3 -2 -1 0 1   
...  
Matrix B (copy of A):  
...  
First matrix:  
1 2 3  
4 5 6  
Second matrix:  
7 8 9  
Matrix F = (A + 5 * B) / 3:  
...  
Matrix Z = D * B:  
...  
Matrix G = Z - B:  
...  
symetric matrix2 0  

## Functions Overview
1. Matrix Constructor:
- Initializes a matrix with given dimensions and optional initial values.
2. Matrix Operations:
- The following operations are supported:
  - `+`, `-`, `*`, `/` (with both scalars and matrices)
  - `==` to compare two matrices
3. `isSymmetric()`:
- Returns `true` if the matrix is symmetric, otherwise `false`.
4. `generateRandomMatrix(int rows, int cols)`:
- Generates a random matrix with given dimensions and values within a specified range.
5. `inputMatrix(int rows, int cols)`:
- Allows the user to input a matrix row by row.

## Error Handling
- Matrix Dimension Mismatch:
  - If the dimensions of matrices do not match for an operation (e.g., addition or multiplication), an invalid_argument exception is thrown.
- Division by Zero:
  - If a matrix is divided by zero, an error message is displayed.

## Notes
- The program uses dynamic memory allocation for storing matrix values. It is important to ensure proper memory management to avoid leaks.
- The matrix size must be positive for the program to work correctly.
