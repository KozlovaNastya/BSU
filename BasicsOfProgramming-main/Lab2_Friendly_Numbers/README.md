# Friendly Numbers
This project solves the problem of finding friendly numbers in a given range from 0 to the number entered by the user. Friendly numbers are numbers for which the sum of divisors of one number equals another number, and the sum of divisors of the second number equals the first number.

### Example:
The numbers 220 and 284 are friendly numbers because:
- The sum of divisors of 220 (excluding 220) equals 284.
- The sum of divisors of 284 (excluding 284) equals 220.

### Program Description
The program finds all pairs of friendly numbers in the range from 0 to the number entered by the user.

### Algorithm:
- For each number in the range from 1 to N, find its divisors.
- For each number, calculate the sum of its divisors.
- Check if two numbers are friendly: if the sum of divisors of one number equals the other number and vice versa.

### How to Use
1. Clone the repository or download the project files to your computer.

2. Open a terminal and navigate to the project folder.

3. Run the program by typing
4. The program will prompt you to enter the maximum number to search for friendly numbers. Enter the number and receive all pairs of friendly numbers in that range.
