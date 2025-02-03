## Program Description
This C++ program reads a text file, searches for a specific word or phrase, replaces it with another given word or phrase, and writes the modified text to an output file.

## Functionality
1. Reads two strings from `input.txt`:
- `poisk` (search phrase) – read until the first period (.).
- `zamena` (replacement phrase) – rest of the line.
2. Reads and processes the remaining lines from `input.txt`:
- Searches for occurrences of `poisk` in each line.
- Replaces all occurrences with `zamena`.
3. Writes the modified line to `output.txt`.
  
## Error Handling
- Checks if `input.txt` or `output.txt` fails to open.
- Ensures `input.txt` is not empty.

## Example Input (input.txt)
hello. Hi  
This is a hello world example.  
Say hello to everyone!  
## Example Output (output.txt)
This is a Hi world example.  
Say Hi to everyone!  
