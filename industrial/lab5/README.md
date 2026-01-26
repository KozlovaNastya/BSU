# RavnTriangle Program

## Objective
To implement an abstract triangle model with area and perimeter calculation, extend it with additional properties, and demonstrate sorting, comparison, and iteration capabilities.

## Program Structure

### Main Components
- `Triangle` (abstract class): Defines common triangle properties and behavior.
- `RavnTriangle` (derived class): Adds color attributes, comparators, iterable support, and string serialization.
- `TriangleTest` (test class): Demonstrates functionality and sorting mechanisms.

### Input Parameters
- Triangle sides `a`, `b`
- Angle between sides `edge` (degrees)
- Contour color (`contur`)
- Fill color (`zalivka`)

### Validation Logic
1. `a > 0`, `b > 0`
2. `0 < edge < 180`
3. Triangle inequality must be satisfied
4. Color strings must not be null or empty

### Core Algorithms
```java
// Area calculation
double area = 0.5 * a * b * Math.sin(Math.toRadians(edge));

// Perimeter calculation
double c = Math.sqrt(a*a + b*b - 2*a*b*Math.cos(Math.toRadians(edge)));
double perimeter = a + b + c;
```

### Sorting & Comparison

- Natural ordering: by area (`Comparable<Triangle>`)
- Custom comparators:
  - By perimeter
  - By contour color
  - By fill color
  - By side `a`
  - By side `b`
  - By angle

### Additional Features

- Implements `Iterable<Object>` for field iteration
- Index-based field access (`getField(int)`)
- String serialization and parsing constructor
- Locale-aware number parsing

### Key Features

- Robust validation with exceptions
- Multiple sorting strategies
- Clean console output for testing
- Object restoration from string representation
