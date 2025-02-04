## Program Description
This C++ program reads a text file, counts the number of unique English letters (case insensitive), and writes the count along with the distinct letters to an output file.

## Functionality
1. Opens `input.txt` and `output.txt`.
2. Reads the file line by line, processing each character:
- Checks if the character is an English letter (a-z, A-Z).
- Converts uppercase letters to lowercase.
- Tracks unique letters using a boolean array.
3. Counts and stores the distinct letters.
4. Writes the total count and list of unique letters `to output.txt`.

## Error Handling
- Checks if `input.txt` or `output.txt` fails to open.
- Ensures `input.txt` is not empty before processing.

## Example Input (input.txt)
Hello, World!  
This is an Example.  

## Example Output (output.txt)
10  
a d e h i l m o p r s t w x  
