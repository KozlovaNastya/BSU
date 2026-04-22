# Thread Creation in Windows
This is an educational project demonstrating basic multithreading concepts using the Windows API. The application performs parallel data processing (finding extrema and calculating averages) with simulated delays.
# System Components
- *Main Thread* — The orchestrator. It handles user input (array size and elements), creates worker threads, synchronizes their completion, and performs the final array modification.
- *min_max Thread* — Scans the array to find the minimum and maximum elements. Implements a 7ms delay between comparisons to simulate heavy workload.
- *average Thread* — Calculates the arithmetic mean of the array elements. Implements a 12ms delay after each summation.

# Data Synchronization
The threads communicate via a shared *struct* passed as a pointer (`LPVOID`) during thread creation. Synchronization is managed using:
- `CreateThread` for parallel execution.
- `WaitForSingleObject` to ensure the main thread waits for workers to finish before modifying results.
- `Sleep` to control execution timing as per requirements.

# Logic Flow
1. Input: User enters array size and values.
2. Execution: min_max and average threads run concurrently.
3. Wait: main waits for both handles to signal completion.
4. Final Step: The original min and max elements in the array are replaced by the calculated average value.
5. Output: The modified array is printed to the console.
