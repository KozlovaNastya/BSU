# Nested loop
## Program Description
This program finds the minimum element in `array1` that is not present in `array2`. It utilizes assembly language within C++ to efficiently compare elements of both arrays.

## How It Works
1. The user is prompted to enter an integer `N`, where `0 < N < 21`.
2. The user inputs `N` elements for `array1`.
3. The user inputs `N` elements for `array2`.
4. The program uses inline assembly to iterate through `array1` and check for the smallest number not found in `array2`.
5. If such an element is found, it is displayed; otherwise, a message is shown indicating no such element exists.

## Compilation and Execution
### Compilation
To compile this program, use a compiler that supports inline assembly in C++, such as MSVC:
```sh
cl program.cpp
```

### Execution
After compiling, run the program:
```sh
./program.exe
```

## Example Run
```
Enter 0 < N < 21: 5
Enter elements of array1
3 5 7 9 11
Enter elements of array2
2 5 9 11 15
Minimum number in array1 not in array2: 3
```

## Notes
- The program uses `INT_MAX` to track the minimum value.
- Inline assembly is used for efficiency.
- The `loop` instruction is utilized to iterate through the arrays.

## Limitations
- This code is specific to x86 architecture with inline assembly.
- Some modern compilers may not support inline assembly; use MSVC for best compatibility.

