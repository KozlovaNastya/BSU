#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include "Employee.h"

using namespace std;

struct RowLock {
    int empId;
    int readerCount = 0;
    bool isWriting = false;
    CRITICAL_SECTION cs;
    HANDLE canReadEvent;
    HANDLE canWriteEvent;
};

string g_fileName;
vector<RowLock*> g_locks;
CRITICAL_SECTION g_globalCs;

RowLock* GetRowLock(int empId) {
    EnterCriticalSection(&g_globalCs);
    for (auto lock : g_locks) {
        if (lock->empId == empId) {
            LeaveCriticalSection(&g_globalCs);
            return lock;
        }
    }
    RowLock* newLock = new RowLock();
    newLock->empId = empId;
    InitializeCriticalSection(&newLock->cs);
    newLock->canReadEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    newLock->canWriteEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    g_locks.push_back(newLock);
    LeaveCriticalSection(&g_globalCs);
    return newLock;
}

bool FindAndReadEmployee(const string& fileName, int id, employee& emp, streamoff& outPos) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) return false;

    employee temp;
    streamoff pos = 0;
    while (file.read((char*)&temp, sizeof(employee))) {
        if (temp.num == id) {
            emp = temp;
            outPos = pos;
            file.close();
            return true;
        }
        pos += sizeof(employee);
    }
    file.close();
    return false;
}

void WriteEmployeeAt(const string& fileName, streamoff pos, const employee& emp) {
    fstream file(fileName, ios::in | ios::out | ios::binary);
    if (!file.is_open()) return;
    file.seekp(pos, ios::beg);
    file.write((char*)&emp, sizeof(employee));
    file.close();
}

DWORD WINAPI ClientHandler(LPVOID lpParam) {
    HANDLE hPipe = (HANDLE)lpParam;
    PipePacket packet;
    DWORD bytesRead, bytesWritten;

    RowLock* activeLock = nullptr;
    Command activeMode;
    streamoff activeFilePos = -1;

    while (true) {
        if (!ReadFile(hPipe, &packet, sizeof(PipePacket), &bytesRead, NULL) || bytesRead == 0) {
            break;
        }

        if (packet.cmd == CMD_EXIT) break;

        if (packet.cmd == CMD_READ || packet.cmd == CMD_WRITE) {
            employee emp;
            if (!FindAndReadEmployee(g_fileName, packet.empId, emp, activeFilePos)) {
                packet.success = false;
                WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);
                continue;
            }

            activeLock = GetRowLock(packet.empId);
            activeMode = packet.cmd;

            if (packet.cmd == CMD_READ) {
                while (true) {
                    EnterCriticalSection(&activeLock->cs);
                    if (!activeLock->isWriting) {
                        activeLock->readerCount++;
                        ResetEvent(activeLock->canWriteEvent);
                        LeaveCriticalSection(&activeLock->cs);
                        break;
                    }
                    LeaveCriticalSection(&activeLock->cs);
                    WaitForSingleObject(activeLock->canReadEvent, INFINITE);
                }
            }
            else if (packet.cmd == CMD_WRITE) {
                while (true) {
                    EnterCriticalSection(&activeLock->cs);
                    if (!activeLock->isWriting && activeLock->readerCount == 0) {
                        activeLock->isWriting = true;
                        ResetEvent(activeLock->canReadEvent);
                        ResetEvent(activeLock->canWriteEvent);
                        LeaveCriticalSection(&activeLock->cs);
                        break;
                    }
                    LeaveCriticalSection(&activeLock->cs);
                    WaitForSingleObject(activeLock->canWriteEvent, INFINITE);
                }
            }

            packet.empData = emp;
            packet.success = true;
            WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);
        }
        else if (packet.cmd == CMD_SAVE) {
            if (activeLock && activeLock->isWriting && activeFilePos != -1) {
                WriteEmployeeAt(g_fileName, activeFilePos, packet.empData);
                packet.success = true;
            }
            else {
                packet.success = false;
            }
            WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);
        }
        else if (packet.cmd == CMD_RELEASE) {
            if (activeLock) {
                EnterCriticalSection(&activeLock->cs);
                if (activeMode == CMD_READ) {
                    activeLock->readerCount--;
                    if (activeLock->readerCount == 0) {
                        SetEvent(activeLock->canWriteEvent);
                    }
                }
                else if (activeMode == CMD_WRITE) {
                    activeLock->isWriting = false;
                    SetEvent(activeLock->canReadEvent);
                    SetEvent(activeLock->canWriteEvent);
                }
                LeaveCriticalSection(&activeLock->cs);
                activeLock = nullptr;
                activeFilePos = -1;
            }
            packet.success = true;
            WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);
        }
    }

    if (activeLock) {
        EnterCriticalSection(&activeLock->cs);
        if (activeMode == CMD_READ) {
            activeLock->readerCount--;
            if (activeLock->readerCount == 0) SetEvent(activeLock->canWriteEvent);
        }
        else if (activeMode == CMD_WRITE) {
            activeLock->isWriting = false;
            SetEvent(activeLock->canReadEvent);
            SetEvent(activeLock->canWriteEvent);
        }
        LeaveCriticalSection(&activeLock->cs);
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    return 0;
}

void createEmployeeFile(const string& fileName) {
    ofstream file(fileName, ios::binary | ios::trunc);
    int count;
    cout << "Enter number of employees: "; cin >> count;
    for (int i = 0; i < count; i++) {
        employee emp;
        cout << "\nEmployee #" << i + 1 << endl;
        cout << "Enter ID: "; cin >> emp.num;
        cout << "Enter Name: "; cin >> emp.name;
        cout << "Enter Hours: "; cin >> emp.hours;
        file.write((char*)&emp, sizeof(employee));
    }
    file.close();
}

void printEmployeeFile(const string& fileName) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) return;
    employee emp;
    cout << "\n--- Employee File Content ---" << endl;
    cout << "ID\tName\tHours" << endl;
    while (file.read((char*)&emp, sizeof(employee))) {
        cout << emp.num << "\t" << emp.name << "\t" << emp.hours << endl;
    }
    cout << "-----------------------------\n" << endl;
    file.close();
}

int main() {
    InitializeCriticalSection(&g_globalCs);
    int clientCount;

    cout << "Enter binary file name: "; cin >> g_fileName;
    createEmployeeFile(g_fileName);
    printEmployeeFile(g_fileName);

    cout << "Enter number of client processes: "; cin >> clientCount;

    vector<HANDLE> hPipes(clientCount);
    vector<HANDLE> hThreads(clientCount);

    for (int i = 0; i < clientCount; i++) {
        hPipes[i] = CreateNamedPipeA(
            "\\\\.\\pipe\\employee_pipe",
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            clientCount,
            sizeof(PipePacket),
            sizeof(PipePacket),
            0, NULL
        );

        if (hPipes[i] == INVALID_HANDLE_VALUE) {
            cout << "Pipe creation failed!" << endl;
            return 1;
        }

        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        char cmd[] = "Client.exe";
        CreateProcessA(NULL, cmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        cout << "Waiting for Client " << i + 1 << " to connect..." << endl;
        ConnectNamedPipe(hPipes[i], NULL);

        hThreads[i] = CreateThread(NULL, 0, ClientHandler, hPipes[i], 0, NULL);
    }

    WaitForMultipleObjects(clientCount, hThreads.data(), TRUE, INFINITE);
    cout << "\nAll clients disconnected." << endl;

    printEmployeeFile(g_fileName);

    for (auto h : hThreads) CloseHandle(h);
    for (auto lock : g_locks) {
        DeleteCriticalSection(&lock->cs);
        CloseHandle(lock->canReadEvent);
        CloseHandle(lock->canWriteEvent);
        delete lock;
    }
    DeleteCriticalSection(&g_globalCs);

    cout << "Press Enter to exit server...";
    cin.ignore(); cin.get();
    return 0;
}
