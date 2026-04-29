#include <iostream>
#include <windows.h>
#include <string>
#include "../../logic.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    string fileName = argv[1];
    int senderId = stoi(argv[2]);

    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "FileMutex");
    HANDLE hSemEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SemEmpty");
    HANDLE hSemFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SemFull");

    string eventName = "ReadyEvent" + to_string(senderId);
    HANDLE hReady = OpenEvent(EVENT_ALL_ACCESS, FALSE, eventName.c_str());

    SetEvent(hReady);

    while (true) {
        cout << "1 - Send message, 2 - Exit: ";
        int choice; cin >> choice;
        if (choice == 2) break;

        cout << "Enter text: ";
        string input; cin >> input;

        Message msg = { "" };
        strncpy_s(msg.text, input.c_str(), _TRUNCATE);

        cout << "Waiting for space in file..." << endl;

        WaitForSingleObject(hSemEmpty, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);

        fstream f(fileName, ios::in | ios::out | ios::binary);
        writeToQueue(f, msg);
        f.close();

        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemFull, 1, NULL);

        cout << "Message sent!" << endl;
    }

    CloseHandle(hMutex);
    CloseHandle(hSemEmpty);
    CloseHandle(hSemFull);
    CloseHandle(hReady);
    return 0;
}
