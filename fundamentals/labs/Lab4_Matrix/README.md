### Problem Description
In this task, you are given a rectangular matrix of integers, and you need to perform the following operations:
1. Sum the elements in rows that do not contain any zeros.
2. Swap columns in the matrix:
- Swap the first column with the last column, the second column with the second-last column, and so on.

### Description of Operations
#### 1. Sum of Elements in Rows Without Zeros
You need to go through each row of the matrix. For each row, check if it contains any zero. If the row does not contain any zero, sum the elements in that row and add it to the total sum.

#### 2. Swap Columns
Swap columns in pairs:

- Swap the first column with the last column.
- Swap the second column with the second-last column.
- Continue this process until all columns are swapped.

For example, for a matrix with 4 columns:
- Column 1 (index 0) will be swapped with Column 4 (index 3).
- Column 2 (index 1) will be swapped with Column 3 (index 2).

### Example Algorithm
#### Step 1: Sum of Elements in Rows Without Zeros
1. Traverse each row in the matrix.
2. For each row, check if it contains any zero. If it does not, sum the elements of the row and add the sum to the total.
#### Step 2: Swap the Columns
1. For each pair of columns, swap the elements at corresponding positions.
2. Continue swapping until you reach the middle of the matrix (if the number of columns is odd, the middle column remains unchanged).
