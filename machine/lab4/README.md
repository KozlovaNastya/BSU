# Procedures

This project demonstrates the use of Assembly functions with different calling conventions in a C++ application. The goal of each function is to find the **smallest element in the first array that is not present in the second array**, given two integer arrays.

## Files

- `proc.asm`: Contains three Assembly functions using different calling conventions:
  - `FindNum1` using `__stdcall`
  - `FindNum2` using `__cdecl`
  - `FindNum3` using `__fastcall`
- `main.cpp`: Calls the above functions with sample data and prints the result.
- `README.md`: This file.

## Assembly Functions

Each function receives:
- Two arrays (`int*`)
- Size of the arrays (`const int`)
- Initial minimum value (`int`)

Each function returns:
- The smallest value in the first array that does not appear in the second array.

## Compilation

To compile this project, you'll need:
- A 32-bit assembler and linker (e.g., **MASM** for Windows)
- A 32-bit C++ compiler (e.g., **MinGW** or **MSVC**)

### MASM + MSVC (example on Windows):
```bat
ml /c /coff proc.asm
cl main.cpp proc.obj
```

## Output Example

```
There are two arrays:
1 2 5 6 4 3 8 
1 5 6 4 3 9 8 
__stdcall for _FindNum1@16 : 2
__cdecl for _FindNum2 : 2
__fastcall for FindNum3 : 2
```

## Notes

- The functions are equivalent in logic but differ in how arguments are passed and how the stack is managed.
- `__stdcall`, `__cdecl`, and `__fastcall` affect function naming, stack cleanup responsibility, and argument passing (registers vs stack).
- Make sure `proc.asm` and `main.cpp` match naming conventions to avoid linkage issues.
