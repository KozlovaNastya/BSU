# Dynamic Stack Implementation

## Program Description  
This C++ program implements a dynamic stack that can store `double` values. 
The stack automatically resizes when it reaches its capacity. It provides functionality to push elements 
onto the stack, pop elements from the stack, access the top element, and print all elements in the stack.

## Functionality  
1. The program uses a custom `Stack` class to manage the stack.  
2. The stack starts with a default capacity of 10 elements.  
3. The `push` method adds a new element to the stack, resizing the array if necessary.  
4. The `pop` method removes the top element from the stack and throws an exception if the stack is empty.  
5. The `top` method returns the top element without removing it, throwing an exception if the stack is empty.  
6. The `isEmpty` method checks whether the stack is empty.  
7. The `GetSizeArr` method returns the current number of elements in the stack.  
8. The `SetSizeArr` method allows you to set a custom size for the stack, with validation to ensure the size is within the valid range.  
9. The `printStack` method prints all elements of the stack from top to bottom, throwing an exception if the stack is empty.

## Error Handling  
- If the stack is empty, trying to pop an element or access the top element will throw a `runtime_error` with an appropriate error message.  
- If an invalid stack size is provided to the `SetSizeArr` method, an `invalid_argument` exception is thrown.  
- The `printStack` method will throw an exception if the stack is empty when trying to print its elements.

## Example input  
push(13.5);  
push(1.11);  
push(9.18);

## Example output  
full stack: 9.18 1.11 13.5  
After removing 1 element: 1.11 13.5  
Top element: 1.11

## Additional Information  
- The stack will automatically resize if it exceeds the current capacity.  
- The `SetSizeArr` function allows the stack size to be adjusted, but it must stay within the bounds of the stack's allocated memory.
