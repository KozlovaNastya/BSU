# Array Operations Program

This program performs several operations on an integer array, such as calculating the number of sign changes, computing the product of elements between two consecutive zeroes, and modifying the array by moving a specified element. It allows the user to input an array manually or generate random values for the array.

## Features

- Allows the user to input an array of integers, either manually or using random values.
- Calculates the number of sign changes between adjacent elements in the array.
- Computes the product of elements between the first and second zeroes in the array (if present).
- Modifies the array by moving all occurrences of a specified element to the end of the array, replacing them with zeros.
- Handles various input validation to ensure that the user provides valid inputs.

## Input Details

1. **Array Size**: The program prompts the user to enter the array size, ensuring it is within the valid range (1 to 10).
2. **Array Elements**: The user can choose whether to manually enter the array elements or let the program generate them randomly within a user-specified range.

## Functions

### 1. `getValue1(const int nmax)`: 
   - Prompts the user to enter a valid array size (1 to `nmax`). If the user provides an invalid input, they will be prompted again.
   
### 2. `getValue2()`: 
   - Prompts the user to input either `1` (yes) or `0` (no) for whether they want to manually enter the array or use randomly generated values. If the input is invalid, the user is prompted again.

### 3. `getValue3()`: 
   - Prompts the user to enter a valid integer. If the user provides invalid input, they are asked again.

### 4. `znak(int array[], int n)`: 
   - Calculates the number of sign changes between adjacent elements in the array. A sign change occurs when the sign of an element differs from the next element.

### 5. `proiz(int array[], int n)`: 
   - Computes the product of elements between the first and second zero elements in the array. If there are no two consecutive zeroes, the function will notify the user.

### 6. `uborka(int array[], int n, int P)`: 
   - Moves all occurrences of the element `P` in the array to the end, replacing them with zeros. If no such element is found, the user is notified.

## Program Workflow

1. The program asks the user for the size of the array (1 to 10).
2. The user decides whether to input the array manually or have it generated randomly.
3. The program displays the initial array.
4. It calculates and displays the number of sign changes between adjacent elements.
5. It calculates and displays the product of elements between the first and second zero elements (if found).
6. The user is asked to input a value `P`, and the program moves all occurrences of `P` to the end of the array, replacing them with zeros.
7. Finally, the program displays the modified array.

## Example
Enter array size 1 <= array length <= 10 5  
Do you want to enter the array manually? (yes = 1; no = 0) 1  
Enter array elements: 1 -2 3 0 4 
Initial array: 1 -2 3 0 4  
Number of sign changes = 3  
Product of array elements between the first and second zero elements = 0 
Enter the element to be moved 3 
Modified array: 1 -2 0 0 4

## Notes

- The program uses random number generation for the array when the user opts to not input the array manually.
- The array size must be between 1 and 10, inclusive.
- The program handles input validation to ensure that the user provides valid values for the array size, elements, and operations.
