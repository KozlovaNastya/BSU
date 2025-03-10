## Associative containers: Credit Test

### Introduction

This is a `C++` program that reads a list of movies from a file (`DATA.txt`), processes the data, and performs various operations such as sorting, filtering, and modifying movie details. It utilizes basic file handling, sorting algorithms, and string manipulation.

### Features

- Reads movie data from a file.

- Stores movie information including name, year, and actors.

- Sorts movies by year and name.

- Extracts and displays a unique list of all actors.

- Finds and counts movies that do not feature a specified actor.

- Displays movies that feature a specified actor.

- Replaces occurrences of a specific actor's name with another name.

### Error Handing

- File not found or unreadable.
- Incorrect file formatting.
- Missing or invalid data.
- Unexpected errors during processing.

### How to Use

Input File Format (`DATA.txt`)

Each line in the file should be formatted as follows:

```
MovieName;Year;Actor1,Actor2,Actor3
```

#### Example:

```
Inception;2010;Leonardo DiCaprio,Joseph Gordon-Levitt,Ellen Page
Interstellar;2014;Matthew McConaughey,Anne Hathaway,Jessica Chastain
```

#### Expected Output:

```
Sorted Movie List:
inception;2010;leonardo dicaprio,joseph gordon-levitt,ellen page
interstellar;2014;matthew mcconaughey,anne hathaway,jessica chastain

List of All Unique Actors:
anne hathaway
ellen page
jessica chastain
joseph gordon-levitt
leonardo dicaprio
matthew mcconaughey

Count of Movies Without 'andrey': 2

Movies Featuring 'andrey':
There is no such film.

Updated Movie List:
inception;2010;leonardo dicaprio,joseph gordon-levitt,ellen page
interstellar;2014;matthew mcconaughey,anne hathaway,jessica chastain
```
