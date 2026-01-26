# Matrix Sorting Program

## Objective
To sort matrix rows by a specific column or columns by a specific row, with configurable sorting dimensions and validation.

## Program Structure

### Input Parameters
``
java Matrix <type> <k>
``
- **type**: 'rows' (sort rows by column) or 'cols' (sort columns by row)
- **k**: Column/row index for sorting (0-based)
- **n**: Matrix dimension entered interactively

### Validation Logic
1. Minimum 2 command-line arguments
2. Valid type: 'rows' or 'cols' 
3. `n > 1` for valid matrix
4. `0 ≤ k < n` for valid index

### Algorithm Implementation
```java
// Random matrix generation
Random rnd = new Random((new Date()).getTime());
int[][] arr = new int[n][n];
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        arr[i][j] = rnd.nextInt(2 * n + 1) - n;
    }
}
```

### Sorting Logic
1. Sort Rows by Column
```java
int[][] sortedMatrix = new int[n][n];
for (int i = 0; i < n; i++) {
    sortedMatrix[i] = arr[i].clone();
}
Arrays.sort(sortedMatrix, (row1, row2) -> Integer.compare(row1[k], row2[k]));
```
2. Sort Columns by Row
```java
Integer[] columnIndices = new Integer[n];
for (int i = 0; i < n; i++) {
    columnIndices[i] = i;
}
Arrays.sort(columnIndices, (col1, col2) -> 
    Integer.compare(arr[k][col1], arr[k][col2]));
```
### Key Features
- Flexible Sorting: Rows by column or columns by row
- Random Generation: Values from -n to n
- Index Validation: Ensures k within matrix bounds
- Interactive Input: Matrix size from user input
