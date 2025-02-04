# Array Manipulation

## Description
This C++ program performs a series of operations on a user-defined array of integers. The user can input integers into the array (ending with a 0) and then compare the array elements with a specified number. The program will calculate statistics such as the sum, count, and compare the elements to the user-defined number. It also performs various transformations and manipulations on the array based on certain conditions.

## Features
1. Array Input:
    - The user can input integer values for the array, ending the input with the number 0.
2. Comparison:
    - The program compares the elements with a user-defined number and counts how many elements are equal to or greater than it.
3. Sum & Count:
    - The program calculates the sum of the elements and the total number of elements.
4. Arithmetic Mean Replacement:
    - The program replaces all zeros in the array with the arithmetic mean of the elements.
5. Neighboring Interval Sum:
    - Each element in the array is updated by adding the sum of its neighboring elements (with a parameter k=1).
6. Even Number Replacement:
    - All even numbers in the array are replaced with the difference between the maximum and minimum elements.
7. Duplicate Removal:
    - The program removes duplicates in the array, keeping only the first occurrence of each value.

## Instructions
1. Run the Program.
2. Input: Enter a series of integers for the array, ending the input with 0.
3. Comparison Input: After entering the array, input a number to compare with the elements of the array.
4. The program will display:
   - Sum of the array.
   - Count of elements in the array.
   - Count of elements equal to the comparison number.
   - Count of elements greater than the comparison number.
   - Array after replacing zeros with the arithmetic mean.
   - Array after adding the sum of neighboring elements.
   - Array after replacing even numbers.
   - Array after removing duplicates.

## Example Input
Enter the elements of the array (end the input with the number 0):  
5 10 3 0 2 10 0  
Enter the number to compare with: 5

## Example Output
Sum of the numbers: 30  
Number of elements: 6  
Count of numbers equal to 5 = 1  
Count of numbers greater than 5 = 2  
Replace all elements with the arithmetic mean:  
5 10 3 5 2 10 5  
Add to each element in the vector the sum of all numbers from neighboring intervals (parameter k=1):  
15 18 18 20 22 22 15  
Replace all numbers where the number is even:  
15 18 18 20 22 22 15  
Remove all duplicates from the sequence in increasing order, except the first one: 
15 18 20 22  
