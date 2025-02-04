# Merging Two Sorted Files

## Program Description  
This C++ program merges two sorted files (`f1.txt` and `f2.txt`) into a third file (`fout.txt`) in ascending order. The input files should contain integers, and the program reads the integers from these files, compares them, and writes the merged result into the output file.

## Functionality  
1. The program opens two input files (`f1.txt` and `f2.txt`) and one output file (`fout.txt`).
2. Reads integers from both input files.  
3. Merges the integers from the two input files into a sorted order and writes them into the output file (`fout.txt`).
4. The merging process handles cases where one file might end before the other.
5. If one of the input files cannot be opened, an error message is displayed and the program exits. Similarly, if the output file cannot be opened, an error message is displayed and the program exits.

## Error Handling  
- If `f1.txt` or `f2.txt` cannot be opened, the program will output an error message (`"f1 is ERROR"` or `"f2 is ERROR"`) and terminate.
- If `fout.txt` cannot be opened, the program will output an error message (`"fout is ERROR"`) and terminate.
- If the files contain non-integer data, the program assumes it is the end of the file when it encounters data that cannot be interpreted as integers.

## Example input (f1.txt and f2.txt)
**f1.txt:**  
1 4 6 8 10  
**f2.txt:**  
2 3 5 7 9  

## Example output (fout.txt)
1 2 3 4 5 6 7 8 9 10

## Notes  
- The input files must be in sorted order for the merging process to work correctly.
- The program assumes that the files contain integers separated by whitespace (spaces, tabs, or newlines).
- The program writes the merged output to `fout.txt`.
