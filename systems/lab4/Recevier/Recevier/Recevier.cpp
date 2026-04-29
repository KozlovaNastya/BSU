#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "../../logic.h"

using namespace std;

int main() {
    string fileName;
    int recordCount, senderCount;

    cout << "Enter binary file name: "; cin >> fileName;
    cout << "Enter number of records: "; cin >> recordCount;

    fstream file(fileName, ios::out | ios::binary | ios::trunc);
    FileHeader header = { 0, 0, recordCount };
    file.write((char*)&header, sizeof(FileHeader));

    Message emptyMsg = { "" };
    for (int i = 0; i < recordCount; i++) {
        file.write((char*)&emptyMsg, sizeof(Message));
    }
    file.close();

    cout << "Enter number of Sender processes: "; cin >> senderCount;

    HANDLE hMutex = CreateMutex(NULL, FALSE, "FileMutex");
    HANDLE hSemEmpty = CreateSemaphore(NULL, recordCount, recordCount, "SemEmpty");
    HANDLE hSemFull = CreateSemaphore(NULL, 0, recordCount, "SemFull");

    vector<HANDLE> hReadyEvents(senderCount);
    for (int i = 0; i < senderCount; i++) {
        string eventName = "ReadyEvent" + to_string(i);
        hReadyEvents[i] = CreateEvent(NULL, TRUE, FALSE, eventName.c_str());
    }

    for (int i = 0; i < senderCount; i++) {
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        string cmd = "Sender.exe " + fileName + " " + to_string(i);

        if (!CreateProcess(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            cout << "Failed to start Sender " << i << endl;
        }
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    cout << "Waiting for all Senders to be ready...\n";
    WaitForMultipleObjects(senderCount, hReadyEvents.data(), TRUE, INFINITE);
    cout << "All Senders are ready!\n";

    while (true) {
        cout << "\n1 - Read message, 2 - Exit: ";
        int choice; cin >> choice;
        if (choice == 2) break;

        cout << "Waiting for message (if queue is empty, I will block)..." << endl;

        WaitForSingleObject(hSemFull, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);

        fstream f(fileName, ios::in | ios::out | ios::binary);
        Message msg = readFromQueue(f);
        f.close();

        cout << "Received: " << msg.text << endl;

        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemEmpty, 1, NULL);
    }

    CloseHandle(hMutex);
    CloseHandle(hSemEmpty);
    CloseHandle(hSemFull);
    for (auto h : hReadyEvents) CloseHandle(h);

    return 0;
}
