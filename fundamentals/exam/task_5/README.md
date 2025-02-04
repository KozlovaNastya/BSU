## Program Description
This C++ program reads a text file, extracts words from each line based on a given set of separators, checks if they are palindromes, and writes the palindromes to an output file. If no palindromes are found in a line, a corresponding message is written instead.

## Functionality:
1. Reads a string of separators from `input.txt` (first line).
2. Processes the remaining lines by extracting words based on the separators.
3. Checks each extracted word using the `palindrom()` function:
- Compares characters from both ends to determine if the word is a palindrome.
4. Writes all palindromes found in each line to `output.txt`.
5. If a line contains no palindromes, writes `"there is no palindromes"`.

## Error Handling:
- Checks if `input.txt` or `output.txt` fails to open.
- Ensures `input.txt` is not empty before processing.

## Example Input (input.txt):
, .!?  
madam, racecar! hello world. noon  
test civic kayak apple  
12321 45654 789  

## Example Output (output.txt):
madam racecar noon  
civic kayak  
12321 45654  
