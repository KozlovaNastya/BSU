# String

## Program Description
This program processes a user-input string by replacing a specified letter with a given word. The replacement occurs only when the letter is not surrounded by spaces.
The program ensures correct handling of edge cases, such as single-character strings or letters appearing at the beginning or end of the input.

## Functionality
1. User Input:
- The user enters a string.
- The user specifies a letter to be replaced.
- The user provides a replacement word.
2. Replacement Logic:
- The program iterates through each character in the string.
- If the character matches the specified letter and is not surrounded by spaces, it is replaced with the given word.
- Otherwise, the original character remains unchanged.
3. Output:
- The program prints the modified string after applying the replacements.

## Error Handling
1. Empty Input Handling:
- If the user enters an empty string, letter, or replacement word, the program will still execute, but results may be unexpected.
2. Multi-Character Letter Input:
- The program only considers the first character of the specified letter for replacement. If the user enters multiple characters, only the first one is used.
3. Single-Character String Edge Case:
- If the input string contains only one character, the program correctly determines whether the replacement should occur.
4. Windows Console Encoding:
The program uses `SetConsoleCP(1251)` and `SetConsoleOutputCP(1251)` to support extended character sets in the Windows console.

## Example Input
Enter string: a b c d  
Enter letter to replace: b  
Enter a replacement word: XYZ  

## Example Ouput
Result: a b XYZ d  
