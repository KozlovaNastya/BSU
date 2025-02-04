# Rectangle Fit Checker  

## Program Description  
This C++ program determines whether one rectangle can fit completely inside another based on user-provided dimensions.  

## Functionality  
1. Prompts the user to enter the width (`x`) and length (`y`) of the first rectangle.  
2. Prompts the user to enter the width (`a`) and length (`b`) of the second rectangle.  
3. Checks if one rectangle can fit inside the other in any orientation:  
   - If rectangle 1 can fit inside rectangle 2, prints `"You can put 1 in 2"`.  
   - If rectangle 2 can fit inside rectangle 1, prints `"You can put 2 in 1"`.  
   - If neither fits inside the other, prints `"Impossible"`.  

## Error Handling  
- Ensures valid numerical input for rectangle dimensions.  
- Handles cases where the rectangles might fit in different orientations.  

## Example input  
Enter the width of 1 rectangle  
4  
Enter the length of 1 rectangle  
6  
Enter a width of 2 rectangles  
5  
Enter the length of 2 rectangles  
7

## Example output  
You can put 1 in 2
