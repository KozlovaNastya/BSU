## Program Description
This C++ program reads input from a file, generates random numbers within a given range, and sorts them based on the sum of their digits.

## Functionality
1. Reads `n`, `x`, and y from `input.txt`.
2. Validates `n` (1 to 20) and ensures `x ≤ y`.
3. Generates `n` random numbers within the range `[x, y]`.
4. Writes the numbers to `output.txt`.
5. Sorts the numbers based on the sum of their digits using Selection Sort.
6. Writes the sorted numbers to `output.txt`.
   
## Error Handling
- Checks for missing/empty input files.
- Ensures correct input format and range validation.

## Example input (input.txt)
5  
10 50

## Example output (output.txt)
23 41 12 35 47  
sorted:  
12 23 41 35 47
