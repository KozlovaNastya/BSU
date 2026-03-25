#include <iostream>
#include <vector>
#include <windows.h>
#include <process.h>
#include <ctime>

using namespace std;

struct ThreadData {
    int id;
    int arraySize;
    int* array;
    HANDLE hStartEvent;
    HANDLE hStoppedEvent;
    HANDLE hContinueEvent;
    HANDLE hExitEvent;
    CRITICAL_SECTION* pcs;
};

DWORD WINAPI marker(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    srand(data->id);

    WaitForSingleObject(data->hStartEvent, INFINITE);

    vector<int> markedIndices;
    bool shouldExit = false;

    while (!shouldExit) {
        int index = rand() % data->arraySize;

        EnterCriticalSection(data->pcs);
        if (data->array[index] == 0) {
            Sleep(5);
            data->array[index] = data->id;
            Sleep(5);
            markedIndices.push_back(index);
            LeaveCriticalSection(data->pcs);
        }
        else {
            cout << "\nMarker " << data->id << ": "
                << "Marked: " << markedIndices.size()
                << ", Blocked index: " << index << endl;
            LeaveCriticalSection(data->pcs);

            SetEvent(data->hStoppedEvent);

            HANDLE waitHandles[2] = { data->hContinueEvent, data->hExitEvent };
            DWORD res = WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);

            if (res == WAIT_OBJECT_0 + 1) {
                EnterCriticalSection(data->pcs);
                for (int idx : markedIndices) {
                    data->array[idx] = 0;
                }
                LeaveCriticalSection(data->pcs);
                shouldExit = true;
            }
            else {
                ResetEvent(data->hStoppedEvent);
            }
        }
    }
    return 0;
}

void printArray(int* arr, int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter array size: "; cin >> n;
    int* arr = new int[n]();

    int m;
    cout << "Enter number of marker threads: "; cin >> m;

    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);

    HANDLE hStartAll = CreateEvent(NULL, TRUE, FALSE, NULL);
    vector<HANDLE> hThreads(m);
    vector<ThreadData> tData(m);
    vector<HANDLE> hStoppedEvents(m);
    vector<bool> threadActive(m, true);

    for (int i = 0; i < m; i++) {
        tData[i] = { i + 1, n, arr, hStartAll,
                     CreateEvent(NULL, TRUE, FALSE, NULL),
                     CreateEvent(NULL, FALSE, FALSE, NULL),
                     CreateEvent(NULL, FALSE, FALSE, NULL),
                     &cs };
        hStoppedEvents[i] = tData[i].hStoppedEvent;
        hThreads[i] = CreateThread(NULL, 0, marker, &tData[i], 0, NULL);
    }

    SetEvent(hStartAll);

    int activeCount = m;
    while (activeCount > 0) {
        WaitForMultipleObjects(m, hStoppedEvents.data(), TRUE, INFINITE);

        EnterCriticalSection(&cs);
        printArray(arr, n);
        LeaveCriticalSection(&cs);

        int target;
        while (true) {
            cout << "Enter marker ID to terminate (1-" << m << "): ";
            cin >> target;
            if (target >= 1 && target <= m && threadActive[target - 1]) break;
            cout << "Invalid ID or thread already dead.\n";
        }

        SetEvent(tData[target - 1].hExitEvent);
        WaitForSingleObject(hThreads[target - 1], INFINITE);
        threadActive[target - 1] = false;
        activeCount--;

        hStoppedEvents[target - 1] = CreateEvent(NULL, TRUE, TRUE, NULL);

        printArray(arr, n);

        for (int i = 0; i < m; i++) {
            if (threadActive[i]) SetEvent(tData[i].hContinueEvent);
        }
    }

    for (int i = 0; i < m; i++) {
        CloseHandle(hThreads[i]);
        CloseHandle(tData[i].hStoppedEvent);
        CloseHandle(tData[i].hContinueEvent);
        CloseHandle(tData[i].hExitEvent);
    }
    CloseHandle(hStartAll);
    DeleteCriticalSection(&cs);
    delete[] arr;

    cout << "All threads finished. Press Enter to exit.";
    cin.ignore(); cin.get();
    system("pause");
    return 0;
}
