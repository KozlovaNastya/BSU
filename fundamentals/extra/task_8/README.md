# Matrix Row with Consecutive Zeros Finder  

## Program Description  
This C++ program reads a matrix from user input and determines the first row that contains at least `k` consecutive zeros.  

## Functionality  
1. Reads the matrix dimensions (`n` rows and `m` columns) from the user.  
2. Reads the matrix elements (values of `0` and `1`).  
3. Reads an integer `k`, which represents the required number of consecutive zeros.  
4. Iterates through each row to find the first row that contains at least `k` consecutive zeros.  
5. Outputs the row number (1-based index) where the condition is met.  
6. If no such row exists, outputs `0`.  

## Error Handling  
- Ensures valid numerical input for the matrix dimensions and elements.  
- Handles edge cases where no row meets the requirement.  

## Example input  
4 5  
1 0 0 1 0  
0 0 0 1 1  
1 1 0 0 0  
0 1 1 1 0  
3

## Example output  
2
