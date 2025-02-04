# Library Management System

## Program Description
This C++ program implements a simple Library Management System that allows users to manage a collection of books. 
The program reads book data from a file, stores the information in a set (to keep books sorted and unique), 
and provides various functions to manipulate and search for books.

## Features
1. __Load Books from File__: Reads book data from `books.txt`.
2. __Display Library__: Shows a list of all books in the library.
3. __Add a Book__: Adds a new book to the library.
4. __Remove a Book__: Deletes a book by title.
5. __Find a Book by Title__: Searches for a book by its title and displays details.
6. __Find Books by Author__: Lists all books written by a specific author.
7. __Add an Author to a Book__: Adds an additional author to an existing book.
8. __Remove an Author from a Book__: Deletes an author from a specific book.

## File Format (books.txt)
Each book should be listed in the following format:  
`UDC_NUMBER;Author1,Author2;Title;Year`

## Usage
1. Ensure `books.txt` is in the same directory as the executable.
2. Run the program to see the list of books and perform operations.
3. Follow on-screen instructions for adding, removing, and searching for books.

## Example Input:
```
12345;John Doe,Jane Smith;Introduction to C++;2020
67890;Alice Brown;Data Structures and Algorithms;2018
```

## Example Output
```
List of books in the library:
UDC: 12345
Authors: John Doe, Jane Smith
Title: Introduction to C++
Year of publication: 2020

Book found:
UDC: 67890
Authors: Alice Brown
Title: Data Structures and Algorithms
Year of publication: 2018

Author added to book: Databases
Book removed: Programming
Updated list of books in the library...
```
