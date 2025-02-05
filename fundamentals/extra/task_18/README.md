# Number Extraction Program

This program extracts and displays valid numbers from a given string. It identifies integers, floating-point numbers, and numbers in scientific notation while ignoring non-numeric tokens. The program efficiently processes the input string using C++ string operations.

## Features

- Parses a string containing numbers and non-numeric characters.
- Identifies and extracts valid numeric values, including:
  - Positive and negative integers.
  - Floating-point numbers.
  - Scientific notation numbers (e.g., `1.23e-4`).
- Uses `stod()` for number validation and conversion.
- Filters out invalid tokens such as words and special characters.

## Input and Output

### Input:
A predefined string containing numbers, words, and special characters:
```cpp
string str = " 34 BGU 67U -9e + 678e+2;;; -5; 1 + 2;; 123E-2 - k345; :-1s1 77e + 22";
```

### Output:
The program extracts and prints only valid numeric values:
```
34
-9e
678e+2
-5
1
2
123E-2
77e
22
```

## Functions

### `main()`
- Initializes a string with mixed content.
- Uses delimiters (`",;:"`) to tokenize the string.
- Identifies valid numbers based on:
  - Presence of digits.
  - Leading `+` or `-` signs.
  - Scientific notation format.
- Prints extracted numbers to the console.

## Notes

- The program assumes well-formed numeric values.
- Uses `stod()` for validation, ensuring only proper numbers are displayed.
- Handles special cases like numbers with suffixes (`l, L, u, U, f, F`).
- Outputs only valid numbers, ignoring non-numeric substrings.
