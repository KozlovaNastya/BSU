# Matrix Row Swap Program

## Objective
To demonstrate matrix creation, manipulation, and row swapping by identifying minimum and maximum elements in a specified column.

## Program Structure

### Main Components
- `Matrix` class: Implements a 2D matrix with constructors, element access, resizing, and utility methods.
- `MatrixTest` class: Tests matrix functionality and performs the task logic.

### Input Parameters
- Array of `Matrix` objects
- Column index `k` (0-based) used to find minimum and maximum values

### Validation Logic
1. Matrix dimensions must be greater than zero
2. Row and column indices must be within bounds
3. Column index `k` must satisfy `0 ≤ k < number of columns`

### Core Algorithm
```java
int[] minMaxRows = matrix.findMinMaxRowsInColumn(k);
int minRow = minMaxRows[0];
int maxRow = minMaxRows[1];

if (minRow != maxRow) {
    matrix.swapRows(minRow, maxRow);
}
```
### Supporting Features
- Multiple constructors (default, square, rectangular, copy)
- Dynamic resizing with data preservation
- Random matrix filling within a specified range
- Submatrix printing for formatted output

### Key Features
- Safe index validation with exceptions
- Reusable matrix operations
- Clear console output before and after processing
- Works with matrices of different sizes
