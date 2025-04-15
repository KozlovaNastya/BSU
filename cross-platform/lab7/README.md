# Composite Pattern

This C++ program provides an object-oriented solution for solving **linear**, **quadratic**, and **composite** equations using polymorphism. It features a base class `Equation` and derived classes for `LinearEquation`, `QwadricEquation` (quadratic), and a container class `CompositeEquation` to hold and manage multiple equations.

## Structure

- **Equation**: Abstract base class with pure virtual functions.
- **LinearEquation**: Derived class for equations of the form `ax + b = 0`.
- **QwadricEquation**: Derived class for quadratic equations of the form `ax² + bx + c = 0`.
- **CompositeEquation**: A composite pattern implementation that aggregates multiple `Equation` objects and allows solving them collectively.

## Files

- `main.cpp` – Entry point of the program.
- `composite.cpp` – Implementation of equation solving logic.
- `composite.h` – Class definitions and interface declarations.


## Example Output

```
1x + 2 = 0
solution: x = -2

2x^2 + 2x + 5 = 0
no real solutions

3
```

The program:
- Solves and prints each equation in the composite.
- Displays the sum of leading coefficients (`a` values) at the end.

## Features

- Supports both **linear** and **quadratic** equations.
- Handles edge cases like:
  - Infinite solutions
  - No solution
  - Complex roots
- Uses polymorphism and dynamic memory management.
- Composite pattern for grouping multiple equations.

## Notes

- The class is named `QwadricEquation` intentionally or mistakenly (should be `QuadraticEquation`).
- Make sure to compile with a C++11-compliant compiler.
- Memory is managed manually; smart pointers could improve safety.
