## Program Description
This C++ program generates an n × n matrix, filling it in a specific pattern using prime numbers, and writes the result to an output file. The program reads the matrix size from an input file and ensures that the matrix size is within a valid range.

## Functionality
1. Reads an integer `n` (matrix size) from `input.txt`.
2. Validates that `n` is between 3 and 100.
3. Creates an `n` × `n` matrix initialized with zeros in the upper triangular part.
4. Fills the lower triangular part in a zigzag pattern using consecutive prime numbers:
- Alternates between column-wise and row-wise filling.
- Uses `prostoe()` function to generate prime numbers sequentially.
- Writes the resulting matrix to `output.txt`.

## Error Handling
- Checks if input.txt or output.txt fails to open.
- Ensures the input file is not empty.
- Validates that n is within the correct range (3 ≤ n ≤ 100).

## Example Input (input.txt)
5

## Example Output (output.txt)
2   3  5  7 11  
13  0  0  0  0  
17 19  0  0  0  
23 29 31  0  0  
37 41 43 47  0  
