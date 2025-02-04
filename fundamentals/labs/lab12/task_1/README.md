# Sieve of Eratosthenes

## Program Description
This C++ program finds all prime numbers up to a given number N using
the Sieve of Eratosthenes algorithm. The program takes an integer
input from the user and outputs all prime numbers up to that value.

## Features
1. Implements the Sieve of Eratosthenes, an efficient algorithm for finding prime numbers.
2. Uses a set data structure to store prime numbers dynamically.
3. Takes user input and validates it.
4. Handles edge cases where `N < 2` (since there are no prime numbers less than 2).

## How It Works
1. The user enters a number `N`.
2. The function `sieveOfEratosthenes(N)`:
    - Initializes a set containing all numbers from 2 to N.
    - Iterates through numbers up to sqrt(N), removing multiples of found primes.
    - Returns the remaining numbers as prime numbers.
3. The program prints all prime numbers up to N.

## Example Input
Enter number N: 30

## Example Output
Prime numbers <= 30: 2 3 5 7 11 13 17 19 23 29

### Edge Cases Handled
- If `N < 2`, the program displays a message and exits.
- Efficiently removes non-prime numbers using the Sieve of Eratosthenes algorithm.
- Uses a `set` to ensure unique prime values and avoid redundant checks.
