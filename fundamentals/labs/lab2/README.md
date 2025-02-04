# Friendly Numbers

## Program Description
This C++ program finds and displays amicable numbers (friendly numbers) within a given limit. Amicable numbers are two different numbers where the sum of the proper divisors of each number equals the other.

## Functionality
1. The user inputs an integer `N` (upper limit).
2. The program iterates through numbers from `1` to `N-1`:
- Computes sum of divisors (`s1`) for `i`.
- Computes sum of divisors (`s2`) for `s1`.
3. Checks if `s1` and `s2` form an amicable pair.
4. Displays all found amicable pairs.
5. If no pairs are found, it prints "`There are no friendly numbers in the given range`".

## Error Handling
- No direct error handling for invalid input (e.g., non-numeric values).
- Ensures that `s1` > `i` to avoid duplicates and redundant checks.

## Example Input
Enter a limit  
300  

## Example Output
Numbers 220 and 284 are friendly  
