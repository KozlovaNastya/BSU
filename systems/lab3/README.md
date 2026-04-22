# Laboratory Work 3: Multithreading and Synchronization

## Project Description
This project demonstrates thread synchronization in Windows using the C++ programming language. The application manages a set of "marker" threads that compete for resources within a shared integer array.

## Core Functionality
The program initializes a shared array and launches a user-specified number of marker threads. Each thread performs the following cycle:
1. Waits for a global start signal.
2. Selects a random index in the array.
3. If the element is 0, the thread marks it with its unique ID after a short delay.
4. If the element is already marked by another thread, the marker thread stops and signals the main process.
5. The thread then waits for either a "Continue" or "Exit" command from the main process.
6. Upon receiving an "Exit" command, the thread clears all its marks from the array before terminating.

## Synchronization Objects Used
- **Critical Sections**: Used to ensure mutually exclusive access to the shared array, preventing race conditions.
- **Manual-Reset Events**: Used to start all threads simultaneously and to handle thread-stop notifications.
- **Auto-Reset Events**: Used for individual thread communication (Continue/Exit signals).

## How to Build and Run
1. Open the project in Microsoft Visual Studio.
2. Ensure the platform is set to x86 or x64.
3. Build the solution.
4. Run the executable.
5. Follow the console prompts to enter array size and the number of threads.
6. Interact with the running threads by choosing which marker to terminate when prompted.

## Unit Testing
The project includes a native C++ unit test suite that verifies:
- Proper marking and cleaning of the shared array.
- Correct thread behavior when the array is completely full.
- Functionality of the resume (Continue) signal.
