# Expression Evaluator Using Stack

This program is a simple expression evaluator that uses a stack data structure to evaluate mathematical expressions in infix notation. The program supports operators like `+`, `-`, `*`, and `/`. It first converts the infix expression to postfix notation and then evaluates the postfix expression.

## Features

- Converts infix expressions to postfix (Reverse Polish Notation).
- Evaluates postfix expressions to compute the result.
- Supports basic arithmetic operators: `+`, `-`, `*`, and `/`.
- Handles parentheses to preserve operation precedence.
  
## Requirements

- C++11 or later
- Windows environment (for `SetConsoleCP` and `SetConsoleOutputCP` used to handle character encoding)

## Code Explanation

The program consists of the following main components:

1. **TStack Structure**: Defines a stack with the following attributes:
   - `n`: Maximum size of the stack.
   - `items`: Array of strings representing the stack's items.
   - `top`: Index to track the top of the stack.

2. **Functions**:
   - `createStack`: Initializes the stack by allocating memory for the specified number of elements.
   - `deleteStack`: Frees the memory allocated for the stack.
   - `push`: Adds an item to the stack.
   - `pop`: Removes and returns the top item from the stack.
   - `isEmpty`: Checks if the stack is empty.
   - `priority`: Determines the precedence of an operator (`+`, `-`, `*`, `/`).

3. **Main Function**:
   - The user inputs an infix expression.
   - The program parses the expression and converts it to postfix notation.
   - It then evaluates the postfix expression by using a stack.
   - The result is displayed.

## How It Works

1. **Input**: The user is prompted to enter a mathematical expression (e.g., `3 + 5 * (2 - 8)`).
2. **Infix to Postfix Conversion**: The program converts the given infix expression to postfix using a stack, ensuring that operator precedence and parentheses are respected.
3. **Evaluation**: The postfix expression is then evaluated using a stack, and the result is printed.

## Example

### Input:
Enter an expression: 3 + 5 * (2 - 8)

### Output:
3 5 2 8 - * + -13

**Explanation**:
- First, the expression is converted into postfix notation: `3 5 2 8 - * +`.
- The postfix expression is then evaluated: `(2 - 8) = -6`, then `5 * -6 = -30`, and finally `3 + -30 = -13`.


## Notes
- The program uses the Windows-specific `SetConsoleCP` and `SetConsoleOutputCP` functions to set the console's character encoding to `1251`. These functions are required for non-English characters, such as Cyrillic characters.
- The stack is limited to a size of 40 in this implementation, which can be adjusted in the `createStack` function if needed.
