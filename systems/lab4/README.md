# Interprocess Communication (IPC) via Binary File

## Project Description
This project demonstrates inter-process communication (IPC) and synchronization in Windows using C++. The application manages a "Receiver" process and multiple "Sender" processes that exchange messages through a shared binary file organized as a FIFO (First-In-First-Out) circular queue.

## Core Functionality
The system implements a classic Producer-Consumer pattern using the file system as shared memory. The workflow includes:
1. **Receiver** initializes a binary file with a metadata header and pre-allocated message slots.
2. **Receiver** launches a specified number of **Sender** processes via command-line arguments.
3. **Sender** processes input text from the console and attempt to write it to the next available slot in the file.
4. **Receiver** reads messages from the file in the order they were sent.
5. If the file is full, **Senders** block and wait for space. If the file is empty, the **Receiver** blocks and waits for new data.

## Shared File Structure (Circular Buffer)
- **Header**: Stores the `head` index (for reading), `tail` index (for writing), and the total capacity of the file.
- **Message Slots**: Fixed-size blocks (20 bytes each) that store the message text.
- **FIFO Logic**: Indices wrap around to the beginning of the data block once they reach the end of the file, ensuring continuous reuse of space.

## Synchronization Objects Used
- **Mutex (FileMutex)**: Ensures that only one process can perform read/write operations on the file at any given time.
- **Semaphores**:
    - `SemEmpty`: Tracks available empty slots. Senders decrement this before writing.
    - `SemFull`: Tracks available messages. Receiver decrements this before reading.
- **Events**: Manual-reset events used by each Sender to signal the Receiver that they have successfully initialized and are ready to work.

## How to Build and Run
1. Open the solution in Microsoft Visual Studio.
2. Ensure both **Receiver** and **Sender** projects are compiled.
3. Place `Sender.exe` in the same directory as `Receiver.exe`.
4. Run `Receiver.exe`.
5. Enter the binary file name, queue size, and number of Sender processes.
6. Use the console menus in each process to send or read messages.

## Unit Testing
The project includes a Native C++ Unit Test suite that validates:
- **Header Initialization**: Ensures the file metadata is correctly formatted.
- **FIFO Logic**: Verifies that messages are read in the exact order they were written.
- **Circular Wrap-around**: Confirms that indices correctly reset to zero when reaching the file capacity without data corruption.
