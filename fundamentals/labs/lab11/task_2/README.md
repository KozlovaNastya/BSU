# Student Data Processing

## Program Description
This C++ program reads student data from an input file, processes it, and writes the processed data into two output files. The program is designed to:
1. Sort students by surname and save the results in Fio.txt.
2. Sort students by course, group, and surname and save the results in Grops.txt.

## Files
- Input File:
    - `Students.txt` (Contains student data in the format: Name;Course;Group)
- Output Files:
    - `Fio.txt` (Sorted by surname)
    - `Grops.txt` (Sorted by course, group, and surname)

## Program Overview
1. Read Data:
- The program reads student data from the `Students.txt` file. The student data consists of the student's full name, course, and group, separated by semicolons (;).
2. Data Structures:
- A Student structure is used to store the student's name, course, and group.
3. Sorting:
- The students are sorted by surname and saved in `Fio.txt`.
- The students are sorted by course, group, and surname and saved in `Grops.txt`.
4. Output:
- The sorted data is written into two separate output files: `Fio.txt` and `Grops.txt`.
5. Error Handling:
- The program checks if the `Students.txt` file can be opened. If it cannot, it prints an error message.
- If the file is empty, an error message is displayed.

## How to Use
1. Prepare the input file (`Students.txt`):
- The input file should contain student data in the following format:  
Name;Course;Group  
For example:  
```
Ivanov Ivan Ivanovich;3;2
Petrov Petr Sergeyevich;2;1
```
2. Run the Program:
- Compile and run the C++ program.
- The program will read data from `Students.txt`, process it, and output two files: `Fio.txt` and `Grops.txt`.
3. View the Output:
- After running the program, check the `Fio.txt` and `Grops.txt` files. These files will contain the sorted student data.

### Example Output
`Fio.txt` (Sorted by surname):
```
Ivanov Ivan Ivanovich;3;2
Petrov Petr Sergeyevich;2;1
Sidorova Anna Pavlovna;1;1
```
`Grops.txt` (Sorted by course, group, and surname):
```
Sidorova Anna Pavlovna;1;1
Petrov Petr Sergeyevich;2;1
Ivanov Ivan Ivanovich;3;2
```
