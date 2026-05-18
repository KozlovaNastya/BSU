# Process Synchronization via Named Pipes

## Project Description
This project demonstrates advanced inter-process communication (IPC) and fine-grained data synchronization using Windows Named Pipes in C++. The application implements a multi-threaded Server process acting as a local database manager and a Client process that allows concurrent reading and modifying of rows inside a binary file without full-file blocking.

## Core Functionality
The system utilizes a row-level locking mechanism implementing the classic **Readers-Writers** pattern for an employee database:
1. **Server** initializes a binary file containing `employee` records (ID, Name, Working Hours).
2. **Server** creates instances of a duplex Named Pipe (`\\.\pipe\employee_pipe`) and spawns dedicated worker threads (`CreateThread`) to handle each incoming Client connection concurrently.
3. **Clients** connect to the pipe and request operations using an employee's unique ID as a key.
4. **Synchronization Logic**:
   - Multiple clients can **read** (`CMD_READ`) the same record simultaneously without blocking each other.
   - If a client requests a **modification** (`CMD_WRITE`), the server blocks access to this specific record for all other clients until the editing is saved or canceled.
   - New readers are strictly blocked if a writer is currently modifying the record.

## Technical Protocol (Shared Structures)
All communications over the pipe exchange a fixed-size network packet defined in `Employee.h`:
- `employee`: Holds core database fields (`int num`, `char name[10]`, `double hours`).
- `PipePacket`: Encapsulates the explicit command state (`CMD_READ`, `CMD_WRITE`, `CMD_SAVE`, `CMD_RELEASE`, `CMD_EXIT`), data transfer payload, and server response validation flags.

## Synchronization Objects Used
- **Critical Sections (`CRITICAL_SECTION`)**: Used inside the server to protect row metadata maps and atomically modify tracking counters (`readerCount`, `isWriting`).
- **Manual-Reset Events (`HANDLE`)**:
  - `canReadEvent`: Signals waiting reader threads when a writer finishes and leaves.
  - `canWriteEvent`: Signals waiting writer threads when the active writer leaves or the active reader count drops exactly to zero.

## How to Build and Run
1. Open the root directory containing the main `CMakeLists.txt` file.
2. Build the solution using a C++17 compatible compiler (e.g., MSVC via Visual Studio).
3. Copy the compiled `Client.exe` executable into the same folder where `Server.exe` resides.
4. Launch `Server.exe`, input initial database setup, and specify the number of parallel clients.
5. Interact with individual generated client consoles to test mutual exclusion and cross-process blocking constraints.

## Unit Testing
The project includes a Native C++ Unit Test suite targeting the server core component to verify:
- **Parallel Read Operations**: Assures concurrent read queries do not block each other.
- **Writer Exclusion Block**: Verifies that any modifying process isolates the target entry.
- **Reader Exclusion Block**: Verifies that an open write handle locks out potential new readers.
- **Signal Integrity**: Validates that event states change correctly when active locks are removed.
