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
The Godfather;1972;Marlon Brando,Al Pacino,James Caan
The Shawshank Redemption;1994;Tim Robbins,Morgan Freeman,Bob Gunton
Pulp Fiction;1994;John Travolta,Uma Thurman,Samuel L. Jackson
Forrest Gump;1994;Tom Hanks,Robin Wright,Gary Sinise
Fight Club;1999;Brad Pitt,Edward Norton,Helena Bonham Carter
The Matrix;1999;Keanu Reeves,Laurence Fishburne,Carrie-Anne Moss
The Prestige;2006;Hugh Jackman,Christian Bale,Michael Caine
The Dark Knight;2008;Christian Bale,Heath Ledger,Aaron Eckhart
Inception;2010;Leonardo DiCaprio,Joseph Gordon-Levitt,Ellen Page
Interstellar;2014;Matthew McConaughey,Anne Hathaway,Jessica Chastain

List of All Unique Actors:
Marlon Brando
Al Pacino
James Caan
Tim Robbins
Morgan Freeman
Bob Gunton
John Travolta
Uma Thurman
Samuel L. Jackson
Tom Hanks
Robin Wright
Gary Sinise
Brad Pitt
Edward Norton
Helena Bonham Carter
Keanu Reeves
Laurence Fishburne
Carrie-Anne Moss
Hugh Jackman
Christian Bale
Michael Caine
Heath Ledger
Aaron Eckhart
Leonardo DiCaprio
Joseph Gordon-Levitt
Ellen Page
Matthew McConaughey
Anne Hathaway
Jessica Chastain

Count of Movies Without 'andrey':
10

Movies Featuring 'andrey':
there is no such films

Replacing 'andrey' with 'andrey':
(no changes made since 'andrey' was not found)

Updated Movie List:
The Godfather;1972;Marlon Brando,Al Pacino,James Caan
The Shawshank Redemption;1994;Tim Robbins,Morgan Freeman,Bob Gunton
Pulp Fiction;1994;John Travolta,Uma Thurman,Samuel L. Jackson
Forrest Gump;1994;Tom Hanks,Robin Wright,Gary Sinise
Fight Club;1999;Brad Pitt,Edward Norton,Helena Bonham Carter
The Matrix;1999;Keanu Reeves,Laurence Fishburne,Carrie-Anne Moss
The Prestige;2006;Hugh Jackman,Christian Bale,Michael Caine
The Dark Knight;2008;Christian Bale,Heath Ledger,Aaron Eckhart
Inception;2010;Leonardo DiCaprio,Joseph Gordon-Levitt,Ellen Page
Interstellar;2014;Matthew McConaughey,Anne Hathaway,Jessica Chastain

```
