# Matrix and Rational Number Library

## Overview
This project implements a matrix library with support for rational numbers. It provides operations on matrices, including addition, subtraction, multiplication, transposition, rank computation, and inversion (for square matrices). The library also defines a `Rational` class for working with rational numbers.

## Features
- **Rational Number Class (`Rational`)**
  - Supports arithmetic operations (`+`, `-`, `*`, `/`)
  - Reduces fractions automatically
  - Supports comparison operations
  
- **Matrix Class (`Matrix<M, N, Field>`)**
  - Supports general rectangular matrices of any size
  - Arithmetic operations: `+`, `-`, `*` (scalar and matrix multiplication)
  - Transposition
  - Rank calculation
  - Row and column access
  
- **Square Matrix Class (`SquareMatrix<N, Field>`)**
  - Inherits from `Matrix<N, N, Field>`
  - Determinant calculation
  - Trace computation
  - Matrix inversion
  
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
