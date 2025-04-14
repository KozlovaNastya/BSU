# Matrix and Rational Number Library

## Overview
This project provides a `C++` library for working with matrices and rational numbers. It includes support for both rectangular and square matrices with customizable numeric types, including a `Rational` class for exact arithmetic. The library supports various matrix operations such as addition, subtraction, multiplication, transposition, rank computation, and inversion (for square matrices).

## Features
- **Rational Number Class (`Rational`)**
  - Supports arithmetic operations (`+`, `-`, `*`, `/`)
  - Reduces fractions automatically
  - Supports comparison operations
  
- **Matrix Class (`Matrix<M, N, Field>`)**
  - Template-based support for arbitrary matrix sizes and numeric types
  - Matrix operations:
    - Addition and subtraction
    - Scalar and matrix multiplication
    - Transposition
    - Rank calculation
  - Element and substructure access:
    - Access individual elements: matrix(i, j)
    - Access rows and columns: getRow(i), getColumn(j)
    - Access via operator overloading: matrix[i][j]
  
- **Square Matrix Class (`SquareMatrix<N, Field>`)**
  - Inherits all features of the general Matrix class
  - Additional operations for square matrices:
    - Determinant calculation
    - Trace computation
    - Matrix inversionn
  
## Dependencies
- C++ Standard Library (`iostream`, `vector`, `stdexcept`, `cmath`, `numeric`)

## Usage
To use the library, include the provided classes and instantiate matrices with desired types.

### Example Usage
```cpp
#include <iostream>
#include "Matrix.h" // Assume the implementation is inside Matrix.h

int main() {
    Matrix<3, 4, int> A({ {1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 1} });
    std::cout << "Matrix A:\n" << A << std::endl;
    
    SquareMatrix<2, Rational> B({ {Rational(1, 2), Rational(3, 4)}, {Rational(5, 6), Rational(7, 8)} });
    std::cout << "Determinant of B: " << B.det() << std::endl;
    
    return 0;
}
```
