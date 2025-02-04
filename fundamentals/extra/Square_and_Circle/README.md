# Square Inside Circle Checker  

## Program Description  
This C++ program determines whether a given square can fit inside a circle based on user-provided dimensions.  

## Functionality  
1. Prompts the user to enter the side length of a square (`a`).  
2. Prompts the user to enter the radius of a circle (`r`).  
3. Checks if the square can fit inside the circle using the diagonal formula:  
   - The square fits if `a ≤ r * sqrt(2)`.  
4. Outputs `"Possible"` if the square can fit, otherwise `"Impossible"`.  

## Error Handling  
- Ensures valid numerical input for the square's side and circle's radius.  
- Handles edge cases where the square is exactly equal to the circle’s diagonal limit.  

## Example input  
Enter the side of the square  
5  
Enter the radius of the circle  
4

## Example output  
Possible
