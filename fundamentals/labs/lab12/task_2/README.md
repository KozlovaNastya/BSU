# Word Frequency Counter

## Program Description
This C++ program reads words from a file (`input.txt`),
processes them to remove punctuation, converts them to
lowercase, and then calculates the frequency of each unique word.
It also prints a list of unique words.

## Features
1. Reads words from `input.txt`.
2. Removes punctuation from words.
3. Converts all words to lowercase for case-insensitive comparison.
4. Displays a list of unique words.
5. Counts and prints the occurrences of each word.

## How to Use
1. Prepare the Input File:
    - Create a text file named `input.tx`t in the same directory as the program.
    - Add some text content to analyze.
3. Compile the Program.
4. Run the Program.
5. Output:
    - A list of unique words.
    - The number of times each word appears in `input.txt`.

## Example Input (input.txt):
`Hello, world! Hello, C++ world.`

## Example Output:
```
Unique words (case insensitive):
c++
hello
world

Word frequency count:
c++: 1
hello: 2
world: 2
```

## Notes
- The program uses set to store unique words and map for counting occurrences.
- Handles punctuation removal and case normalization.
- If the input file is empty or missing, the program displays an error.
