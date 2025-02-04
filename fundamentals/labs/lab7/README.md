# Complex Numbers

## Program Description
This C++ program defines a class ComplexNumbers that represents complex numbers. The program allows the user to perform basic arithmetic operations (addition, subtraction, multiplication, and division) on two complex numbers. The program uses operator overloading to implement these operations, making it easy to work with complex numbers in a natural and intuitive way.

## Functionality
1. Complex Number Class
   
The ComplexNumbers class contains:
- Private Data Members:
  - `real`: The real part of the complex number.
  - `img`: The imaginary part of the complex number.
- Public Methods:
  - Constructor: Initializes the real and imaginary parts. Defaults to 0 + 0i if no arguments are provided.
  - Getters and Setters:
    - `getReal()`: Returns the real part of the complex number.
    - `getImg()`: Returns the imaginary part of the complex number.
    - `setReal()`: Sets the real part of the complex number.
    - `setImg()`: Sets the imaginary part of the complex number.
  - Operator Overloading:
    - `operator+`: Adds two complex numbers.
    - `operator-`: Subtracts two complex numbers.
    - `operator*`: Multiplies two complex numbers.
    - `operator/`: Divides one complex number by another. If the divisor is zero (0 + 0i), an error message is displayed, and the result is 0 + 0i.
  - Print Method:
    - Displays the complex number in the form a + bi or a - bi (where a is the real part and b is the imaginary part).

2. User Input and Operations
- The program prompts the user to enter:
  - The real and imaginary parts of two complex numbers.
  - An operation symbol (+, -, *, or /) to perform on the complex numbers.
- The program then performs the requested operation on the complex numbers and displays the result.

## Error Handling
- Division by Zero:
  - If the user tries to divide by a complex number 0 + 0i, the program displays an error message:
makefile  
`Error: division by 0!`
  - It then returns 0 + 0i as the result for division.
- Unknown Operation:
  - If the user enters an invalid operation symbol (not one of +, -, *, /), the program will display the following error message:  
`Unknown operation sign`
- General Input Error:
  - The program expects valid double values for the real and imaginary parts. If the user enters non-numeric values, the program will handle the error based on the input stream, and it is expected to prompt the user again in such cases.

## Example Input
Enter the real and imaginary part of the first complex number:  
3 4  
Enter the real and imaginary part of the second complex number:  
1 2  
Enter the operation sign:  
+

## Example Output
Add: 
4+6i
