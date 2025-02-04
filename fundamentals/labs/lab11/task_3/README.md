# Train Schedule Management System

## Program Description
The Train Schedule Management System is a C++ application that allows users to manage and filter a train schedule 
by different parameters, including the departure time, station, and train type. The application reads data from a file, 
processes it, and then provides various sorting and filtering options for train schedules.

## Features
1. Data Input:
- The system reads train data from an input file (`trains.txt`),
where each line contains information about a train in the format `numberOfTrain;station;type;departureTime;travelTime`.
2. Sorting:
- Trains can be sorted by departure time.
3. Filtering:
- Users can filter trains by:
   - Time Range:  
     Enter a start time and an end time to display trains that depart within that range.
   - Station:  
     Search for trains arriving at or departing from a specific station.
   - High-Speed Trains:  
     Filter to show only high-speed trains at a given station.
   - Fastest Train:  
     Display the fastest train at a specific station based on its travel time.

## How to Use
### Input Data
- The input data should be in a file called trains.txt, where each line is formatted as follows:
`numberOfTrain;station;type;departureTime;travelTime`
- For example:
```
101;StationA;High-speed;12:30;120
102;StationB;Regular;13:00;180
103;StationA;Regular;14:00;150
```
### Example Execution
```
Enter start time (HH:MM): 12:00
Enter end time (HH:MM): 14:00
101;StationA;High-speed;12:30;120
102;StationB;Regular;13:00;180
103;StationA;Regular;14:00;150

Enter station name: StationA
101;StationA;High-speed;12:30;120
103;StationA;Regular;14:00;150

Enter station name: StationA
Trains at station StationA
101;StationA;High-speed;12:30;120
103;StationA;Regular;14:00;150

Enter station name: StationA
The fastest train at station StationA
101;StationA;High-speed;12:30;120
```

## Code Details
1. Class Train:
    - This class contains attributes such as `numberOfTrain`, `station`, `type`, `departureTime`, and `travelTime`.
    - The class provides getters and setters for these attributes, as well as a `print()` method to display the train's details.
2. Main Function:
    - The `main()` function reads the train data from the `trains.txt` file, stores it in a `vector<Train>`, and allows sorting,
      filtering, and displaying results based on user input.
3. Sorting:
    - Trains are sorted by `departureTime`, and additional sorting criteria are applied based on user queries.
  
## Error Handling
- If the file `trains.txt` is missing or empty, the program will display an error message and exit.
- If invalid or empty input is entered for time or station, the program will prompt the user again for valid input.
