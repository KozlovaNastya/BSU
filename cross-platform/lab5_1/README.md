# Semantics of Moving: Credit Test

This C++ program demonstrates basic OOP concepts, dynamic memory handling, inheritance, polymorphism, and smart pointers by modeling football players and their performance. It includes two main classes:

- `Footballer`: Represents a basic football player.
- `FootballerResult`: Inherits from `Footballer`, adds match statistics.

The program also demonstrates:
- Move constructors and move assignment.
- Operator overloading (`==`, `<<`).
- Use of `std::unique_ptr` and dynamic_cast.
- A filtering function to remove players based on match performance.

## Files

- `footballer.h`: Header file containing the class declarations.
- `footballer.cpp`: Implementation of the classes and their member functions.
- `main.cpp`: Demonstrates usage of the classes and functionality.
- `README.md`: This file.

## Key Features

- **ID Tracking:** Each player is assigned a unique ID.
- **Dynamic Memory:** `FootballerResult` stores dynamic arrays for goals.
- **Inheritance & Polymorphism:** Used to distinguish between basic and result-based footballers.
- **Memory Management:** Ensures proper resource handling using destructors and smart pointers.
- **Data Filtering:** Removes underperforming players from a vector.

## Example Output

```
FOOTBALLER
constructor with parameteres
0;Less;defender;2026
1;Johan;goalkeeper;2030
...
Number of goalkeepers: 2
Number of defenders: 2
...
Removed objects count: 2
```

## Notes

- Players with fewer `realGames` than the threshold passed to `CompressArray()` are removed (set to `nullptr`).
- Attempting to copy objects is disabled — only moving is supported for safe memory management.
