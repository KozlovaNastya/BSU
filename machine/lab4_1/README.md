# Procedures: Credit Test

This project demonstrates how to use an Assembly function with the `__fastcall` calling convention from a C++ program. The function scans a randomly generated array of unsigned integers and returns the **element with the highest frequency**, but **only if it appears more than once**. If no such element exists, it returns `-1`.

## Files

- `main.cpp`: Generates an array of random integers, calls the Assembly function, and displays the result.
- `proc.asm`: Contains the `Find1` function written in x86 Assembly using the `__fastcall` calling convention.

## Functionality

### C++ Side
- Generates 10 random numbers from 0 to 9.
- Calls `Find1()` from Assembly.
- Displays the array and the result.

### Assembly Side (`Find1`)
- Parameters:
  - `ecx`: Pointer to the array.
  - `edx`: Size of the array.
- Logic:
  - Iterates through the array.
  - For each element, counts how many times it appears.
  - Keeps track of the element with the highest count.
  - Returns that element **if** it occurs more than once, otherwise returns `-1`.

## Compilation Instructions

You will need:
- A 32-bit assembler and compiler (e.g., **MASM** + **MSVC** or **MinGW**)

### Example using MASM and MSVC:
```bat
ml /c /coff proc.asm
cl main.cpp proc.obj
```

## Example Output

```
massiv:
3 7 3 1 0 2 6 4 3 2
3
```

## Notes

- The function uses two nested loops to count occurrences.
- If the most frequent element appears **only once**, it is ignored.
- The program uses `__fastcall`, so ensure correct usage of parameter registers (`ecx`, `edx`).
