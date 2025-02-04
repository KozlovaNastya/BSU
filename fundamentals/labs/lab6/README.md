# Files
## Program Description
This program reads text from an input file and processes each line to find the longest strictly increasing substring (a substring where each character is greater than the previous one). For each line, the program identifies the substring with the longest length and prints it.

## Functionality
1. User Input:
- The program reads input from a file called `input.txt`.
- The input file contains multiple lines of text, with each line potentially containing multiple words.
2. Substring Processing:
- For each line of text, the program splits the line into individual words.
- It checks each word to see if its characters are in strictly increasing order.
- If a word meets this criterion, the program compares its length with the previously identified longest increasing word.
- The program keeps track of and returns the longest strictly increasing substring for each line.
3. Output:
- The program prints the longest strictly increasing substring for each line in the format:  
  `Line number. Maximum strictly increasing substring: [substring]`  
  `In line: [original line]`  
- The program processes up to 10 lines from the input file and displays the results.

## Error Handling
1. File Input Error:
- The program checks if the file input.txt can be opened successfully. If not, it will print an error message and terminate. The error message is:
`ERROR with input.txt`  
2. Empty File Handling:
- If the file is empty, the program will not produce any output, as it processes lines and finds substrings only if lines are present.
3. Line Processing Error:
- If no strictly increasing substrings are found in a line, the program simply does not display any output for that line.
4. Maximum Number of Lines Processed
- The program processes a maximum of 10 lines from the input file. After 10 lines, it stops processing.

## Example Input (input.txt)
123456789 pppp  
2354786 bhgv  
66666 123  
ffdasddhjkl 1234  
abcdefg 654  
hijklmnop  
xyz  
55415113 efj hi  
jjhhfss 123 abcd  
opty  
giraf 123 000  
36589  
abcgftx  
op 66666  
gy  
w  
abc  
defg  
hig  
klp

## Example Output
1. Maximum strictly increasing substring: 123456789  
In line: 123456789 pppp

2. Maximum strictly increasing substring: bhgv  
In line: 2354786 bhgv

3. Maximum strictly increasing substring: 123  
In line: 66666 123

4. Maximum strictly increasing substring: ffdasddhjkl  
In line: ffdasddhjkl 1234

5. Maximum strictly increasing substring: abcdefg  
In line: abcdefg 654

6. Maximum strictly increasing substring: hijklmnop  
In line: hijklmnop

7. Maximum strictly increasing substring: xyz  
In line: xyz

8. Maximum strictly increasing substring: efj  
In line: 55415113 efj hi

9. Maximum strictly increasing substring: abcd  
In line: jjhhfss 123 abcd

10. Maximum strictly increasing substring: opty  
In line: opty
