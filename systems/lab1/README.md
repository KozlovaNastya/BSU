# Process Creation in Windows

This is an educational project for the "Programming Technologies" course. The system consists of a main orchestrator application and two utility programs.

## System Components

1. **Main (lab1)** — The primary application. It manages user input, launches utility processes using `CreateProcess`, and displays the final results.
2. **Creator** — A utility for creating a binary file containing employee data (`struct employee`).
3. **Reporter** — A utility that reads the binary file and generates a formatted text report with calculated salaries.

## Data Structure

```cpp
struct employee {
    int num;         // Identification number
    char name[10];   // Name (fixed size for binary recording)
    double hours;    // Hours worked
};
```
