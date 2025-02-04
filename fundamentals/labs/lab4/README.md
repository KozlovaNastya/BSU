# Matrix

## Program Description
This program handles a 2D dynamic array in C++, performing several operations like input, reversing columns, and summing rows without zeros. Here's a breakdown:

## Functionality
1. User Inputs:
- Matrix size (`rows` x `columns`) with constraints (1 ≤ `rows` ≤ 8, 1 ≤ `columns` ≤ 10).
- Choice of input method:
  - Manual input (user enters values).
  - Randomized input (values generated within a specified range).
2. Array Operations:
- Display Array (`massiv`): Prints the matrix.
- Reverse Columns (`Perestanovka`): Flips each row's elements.
- Row Sums (`Sum`): Computes sum of elements in rows that do not contain a zero.

## Error Handling
- Ensures the number of rows and columns is within valid limits (1-8 rows, 1-10 columns).
- If the user enters invalid input (e.g., letters, negative numbers, or out-of-range values), the program displays an error message and asks for re-entry.

## Example Input
Enter array dimension:  
The number of lines must not exceed 8 and be at least 1  
The number of columns must not exceed 10 and be at least 1  
3 4  
1. keyboard input  
2. Enter randomly  
1  
Enter array data:  
5 3 2 7  
0 6 1 9  
4 8 2 0  

## Example Output
Source array:  
5 3 2 7  
0 6 1 9  
4 8 2 0  

Sum of row elements 1 containing no zeros = 17  
All lines contain 0  

Rearranged array:  
7 2 3 5  
9 1 6 0  
0 2 8 4  
