## Associative Containers

This C++ program reads flower bed data from a file, processes and sorts the data based on specific criteria, and performs various analyses on the flower species present.

### Functionality

1. Reads flower bed data from `DATA.txt`.

2. Validates the input file and ensures it is not empty.

3. Parses each flower bed's number, shape, and flower species.

4. Converts all text to lowercase for uniform processing.

5. Sorts the flower beds by shape in descending order (if equal, then by number in ascending order).

6. Displays all unique flower species found in the dataset.

7. Identifies and prints flower beds that do not contain "daisy".

8. Determines and prints flower species common to all flower beds.

9. Counts the number of flower beds containing exactly two types of flowers.

10. Removes all occurrences of "daisy" from the dataset and prints the updated list.

### Error Handling

- Checks if the input file exists and is not empty.

- Ensures correct parsing of data.

- Handles missing or incorrect formatting in the file.

### Example Input (`DATA.txt`)

```
1;Round;Rose,Lily
2;Square;Tulip,Sunflower
3;Oval;Daisy,Rose,Lily
4;Round;Daisy,Tulip
```

### Example Output

```
sorted flowers beds:
2;Square;Tulip,Sunflower
3;Oval;Daisy,Rose,Lily
1;Round;Rose,Lily
4;Round;Daisy,Tulip
all species of flowers:
Daisy
Lily
Rose
Sunflower
Tulip
lines that contain daisy:
2
common flowers:
there is no data
count of lines with 2 types of colors:
2
delete daisy from all lines:
2;Square;Tulip,Sunflower
3;Oval;Rose,Lily
1;Round;Rose,Lily
4;Round;Tulip
```
