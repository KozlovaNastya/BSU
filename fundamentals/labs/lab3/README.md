# Arrays

## Program Description
This C++ program works with an array of integers, providing several functionalities: calculating sign changes, computing the product of elements between zeros, and removing specific elements. The user can input the array elements or fill it with random values within a specified range.

## Functionality
1. User Inputs:
- Array size (`n`), ensuring it's within a valid range (1 to 10).
- Choice of filling the array manually or randomly.
- Random range limits (`niz` for lower, `verh` for upper).
- Element to be removed (`P`).
2. Array Operations:
- Sign Changes: Counts how often consecutive elements have opposite signs.
- Product Calculation: Computes the product of elements between the first two zeros, if present.
- Element Removal: Moves specified elements to the end of the array and replaces them with zeros.
3. Helper Functions:
- `getValue1(int nmax)`: Gets a valid array size input.
- `getValue2()`: Prompts user for input method choice (manual/random).
- `getValue3()`: Gets a valid integer input (for range limits).
- `znak(int array[], int n)`: Counts sign changes in the array.
- `proiz(int array[], int n)`: Calculates the product of elements between the first two zeros.
- `uborka(int array[], int n, int P)`: Removes specified element from the array.

## Error Handling
Ensures inputs are numeric and within valid ranges.
Handles invalid user responses gracefully with prompts to retry.

## Example Input
Enter size 1 <= number of array elements >=10  
5  
Do you want to fill the array yourself? (answers: yes = 1; no = 0)  
1  
Enter Array Elements:  
2 -3 0 4 0  
Enter the element you want to remove  
4  

## Example Output
Source array:  
2 -3 0 4 0   
Number of sign changes = 2  
Product of array elements located between the first and second zero elements = 4  
New array:  
2 -3 0 0 0
