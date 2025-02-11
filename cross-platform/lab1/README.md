# Old British Money System

## Program Description
This program implements a `Money` class in C++, representing the old British monetary system with pounds, shillings, and pence. The program supports arithmetic operations, comparisons, and exception handling for incorrect values and exceeding the maximum limit of 1 billion pounds.

## Features
1. **Money Representation:**
   - Stores monetary values in pounds (pd), shillings (sh), and pence (p).
   - Ensures valid values: shillings must be < 20, pence must be < 12.
2. **Arithmetic Operations:**
   - Supports addition (`+`), subtraction (`-`), compound assignment (`+=`, `-=`).
3. **Unary Operations:**
   - Unary negation (`-`).
4. **Comparison Operators:**
   - Supports equality (`==`) and less-than (`<`) comparisons.
5. **Input and Output:**
   - Overloaded `<<` operator for formatted output.
6. **Exception Handling:**
   - Throws exceptions for invalid shilling/pence values and for exceeding 1 billion pounds.

## Files
1. **`Bank.h`**
   - Defines the `Money` class and exception class `exc`.
2. **`Bank.cpp`**
   - Implements `Money` class methods and operator overloads.
3. **`main.cpp`**
   - Contains the main function to demonstrate class functionality.

## How It Works
1. **Object Creation:**
   - The user can create a `Money` object with pounds, shillings, and pence.
   - If shillings ≥ 20 or pence ≥ 12, an exception is thrown.
   - If pounds exceed 1 billion, an exception is thrown.
2. **Arithmetic Operations:**
   - Addition and subtraction adjust values correctly (e.g., 12 pence converts to 1 shilling).
   - Results exceeding 1 billion pounds trigger an exception.
3. **Comparison Operations:**
   - `==` checks if two money values are equal.
   - `<` compares money values lexicographically (pounds → shillings → pence).
4. **Output Format:**
   - Example outputs:
     ```
     2pd.
     3pd.5sh.
     6sh.3,5p.
     -2pd.
     -6sh.3,5p.
     ```

## Example Usage
```cpp
try {
    Money a(2, 10, 5);
    Money b(1, 15, 8);
    Money c = a + b;
    std::cout << c << std::endl; // Outputs formatted sum
    
    Money d = -a;
    std::cout << d << std::endl; // Outputs negated value

    std::cout << (a < b) << std::endl; // Comparison
} catch (const exc& e) {
    std::cerr << e.what() << std::endl;
}
```

## Error Handling
- **Invalid Values:**
  - If shillings are `>= 20` or pence are `>= 12`, an exception is thrown.
- **Exceeding 1 Billion Pounds:**
  - If any operation results in pounds > 1,000,000,000 or < -1,000,000,000, an exception is thrown.

## Notes
- The program ensures correctness in all operations according to the old British monetary system.
- Arithmetic operations automatically adjust shillings and pence when limits are exceeded.
- Negative values are supported and formatted correctly.
