# Factory Pattern

This C++ project demonstrates the use of the **Factory Method Design Pattern** to create and solve different types of equations—specifically linear and quadratic (misspelled as "Qwadric") equations. The project encapsulates object creation logic into factory classes and method-based static creation for extensibility and clarity.

## Features

- Solve linear equations of the form `ax + b = 0`
- Solve quadratic equations of the form `ax² + bx + c = 0`
- Detect:
  - Infinite or no solutions
  - Determinants and nature of roots
  - Whether a quadratic is a perfect square
- Use of:
  - Abstract base class `Equation`
  - Concrete classes `LinearEquation` and `QwadricEquation`
  - Factory method and class-based factory pattern

## File Structure

- `main.cpp` — Entry point; demonstrates usage of both factory creation methods.
- `factory.h` — Header file defining class interfaces and factories.
- `factory.cpp` — Implementation of equation-solving logic and factory creation methods.

## Sample Output

```text
2x + 6 = 0
0x^2 + 4x + 2 = 0
2x + 3 = 0
1x^2 + 0x + 6 = 0
```

(Actual output may vary depending on logic in `solve()` functions if they are called)

## Code Highlights

- `Equation::CreateEquation(...)`: Static method to create equations using an enum-based switch.
- `LinearEquationFactory` and `QwadricEquationFactory`: Class-based approach to creating equations.
- Use of polymorphism to call `solve()` and `print()` on abstract `Equation` pointers.

## Notes

- Quadratic class name contains a typo: `QwadricEquation` should ideally be `QuadraticEquation`.
- All dynamically allocated equations are manually deleted; consider using smart pointers for memory safety.
- Demonstrates classic OOP principles and design patterns in C++.
