# Virtual class and Inheritance

## Description

This program is designed to solve and manage two types of equations:

1. **Quadratic Equation** (ax² + bx + c = 0)
2. **Linear Equation** (ax + b = 0)

The program performs various tasks such as solving the equations, writing solutions to a file, checking for solutions, and sorting the equations based on their coefficients.

### Features:
- Input quadratic and linear equations.
- Solve the equations and print solutions.
- Save the output to a file called `DATA.txt`.
- Display equations that have no solutions or infinite solutions.
- Sort equations by their leading coefficients and by the second coefficient for linear equations.
- Check special cases for quadratic equations, like having a negative determinant or being a perfect square.
- Display linear equations where the leading coefficient is smaller than the second coefficient and sort them based on the second coefficient.

## Usage

1. Run the program.
2. You will be prompted to choose the type of equation:
   - Type `1` for a **Quadratic Equation**.
   - Type `2` for a **Linear Equation**.
   - Type `3` to **stop** entering equations.
3. Enter the coefficients (a, b, c for quadratic equations and a, b for linear equations) when prompted.
4. After entering the equations, the program will:
   - Print the solutions to the console.
   - Write the equations and their solutions to `DATA.txt`.
   - Display additional information, such as equations with no solutions, equations with infinite solutions, and equations that meet special conditions (e.g., quadratic equations with a negative determinant).
5. The program will also sort and display equations based on their coefficients.

## Output

The program produces two types of outputs:
1. **Console Output**: It displays solutions, conditions, and information about equations.
2. **File Output**: All equations and their solutions are saved to a file called `DATA.txt`. Each equation is followed by its solution or condition (e.g., "no real solutions").

## Example

Here’s an example of how the program runs:

```
chose '1' (Quadratic Equation) or '2' (Linear Equation) or '3' (stop enter) : 1
enter 'a', 'b', 'c' : 1 -3 2
solution: x = 2
first solution: x1 = 2
second solution: x2 = 1
chose '1' (Quadratic Equation) or '2' (Linear Equation) or '3' (stop enter) : 2
enter 'a', 'b' : 2 4
solution: x = -2
chose '1' (Quadratic Equation) or '2' (Linear Equation) or '3' (stop enter) : 3

information was successfully written in DATA.txt
```

## File: `DATA.txt`

The output file `DATA.txt` will contain the equations and their solutions. Example content of the file:

```
1x^2 - 3x + 2 = 0
first solution: x1 = 2
second solution: x2 = 1

2x + 4 = 0
solution: x = -2
```

## Error Handling

- **Invalid Quadratic Equation**: If a quadratic equation has `a == 0`, an exception will be thrown with the message `"Error: this is not a quadratic equation"`.
- **Linear Equation with No Solution**: If `a == 0` and `b != 0`, the program will indicate there is no solution.
- **Linear Equation with Infinite Solutions**: If `a == 0` and `b == 0`, the program will indicate that there are infinite solutions.
