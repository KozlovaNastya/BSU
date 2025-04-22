# Iterator Pattern

This project implements a **custom double-ended queue (Deque)** in C++ with support for **two different iterator types**:
- A **method-based iterator** (`MethodIterator`)
- A **functor-based external iterator** (`DequeIter`)

It demonstrates modern C++ concepts including:
- Copy/move constructors and assignment operators
- Dynamic memory management
- Iterator patterns
- Operator overloading

## Features

- Push and pop elements from both front and back
- Custom `Deque` class with internal dynamic array
- Support for both external (functor-style) and internal (method-style) iteration
- Utility methods like `isEmpty`, `IsFull`, `Size`, `Clear`, `Front`, `Back`
- Overloaded output operator for displaying contents
- Search functions using both iterators: `find1` and `find2`

## File Overview

- `main.cpp` — Contains all class definitions and the main function demonstrating usage.

## Sample Output

```text
constructor without parameteres
deq1 with PushBack
1 2 3 4 5 6
deq2 with PushFront
6 5 4 3 2 1
deq1 with popBack : 6
deq2 with popFront : 6
deq2 with Front : 5
deq2 with Back : 1
deq2 with isEmpty : 0
deq2 with Size : 5
deq2 with IsFull : 0
constructor with parameteres for deq3
7 8 9
deq3 with Clear :
operator deq3 = deq2
5 4 3 2 1
operator deq3 = deq2 with move
5 4 3 2 1
deq2 :
copy constructor for deq4
1 2 3 4 5
copy constructor for deq5 with move
1 2 3 4 5
deq1 :
find1 in deq5 elem 3 : 2
find1 in deq5 elem 9 : -1
find2 in deq5 elem 1 : 0
find2 in deq5 elem 7 : -1
```

## Iterator Details

### `DequeIter` (Functor-style)
Implements iteration via overloaded `operator++`, `operator*`, and `operator()`. Used in `find1`.

### `MethodIterator`
Implements iteration via explicit method calls: `hasNext()`, `current()`, and `next()`. Used in `find2`.

## Best Practices & Notes

- Implements **deep copy** and **move semantics** to manage dynamic memory safely.
- Demonstrates two distinct iterator paradigms in C++.
- Iterator search methods (`find1` and `find2`) return index if found, `-1` if not.
- `IsFull()` is a simulated check by attempting dynamic allocation (educational, not optimal).
