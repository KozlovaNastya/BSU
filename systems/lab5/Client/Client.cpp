#include <iostream>
#include <string>
#include <windows.h>
#include "../lab5/Employee.h"

using namespace std;

int main() {
    HANDLE hPipe;
    DWORD bytesRead, bytesWritten;
    PipePacket packet;

    while (true) {
        hPipe = CreateFileA(
            "\\\\.\\pipe\\employee_pipe",
            GENERIC_READ | GENERIC_WRITE,
            0, NULL, OPEN_EXISTING, 0, NULL
        );

        if (hPipe != INVALID_HANDLE_VALUE) {
            break;
        }

        if (GetLastError() != ERROR_PIPE_BUSY) {
            cout << "Could not open pipe. Retrying..." << endl;
            Sleep(1000);
            continue;
        }

        if (!WaitNamedPipeA("\\\\.\\pipe\\employee_pipe", 5000)) {
            cout << "Could not open pipe: Pipeline is busy." << endl;
            return 1;
        }
    }

    while (true) {
        cout << "\n1 - Modify record\n2 - Read record\n3 - Exit\nChoice: ";
        int choice;
        cin >> choice;

        if (choice == 3) {
            packet.cmd = CMD_EXIT;
            WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);
            break;
        }

        if (choice != 1 && choice != 2) {
            cout << "Invalid choice." << endl;
            continue;
        }

        cout << "Enter employee ID: ";
        int id;
        cin >> id;

        packet.cmd = (choice == 1) ? CMD_WRITE : CMD_READ;
        packet.empId = id;

        WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);

        cout << "Waiting for response from server..." << endl;
        ReadFile(hPipe, &packet, sizeof(PipePacket), &bytesRead, NULL);

        if (!packet.success) {
            cout << "Employee with ID " << id << " not found or access denied." << endl;
            continue;
        }

        cout << "\n--- Employee Data ---" << endl;
        cout << "ID: " << packet.empData.num << endl;
        cout << "Name: " << packet.empData.name << endl;
        cout << "Hours: " << packet.empData.hours << endl;
        cout << "---------------------" << endl;

        if (choice == 1) {
            cout << "Enter new Name: ";
            cin >> packet.empData.name;
            cout << "Enter new Hours: ";
            cin >> packet.empData.hours;

            cout << "\n1 - Save changes to server\n2 - Cancel modifications\nChoice: ";
            int subChoice;
            cin >> subChoice;

            if (subChoice == 1) {
                packet.cmd = CMD_SAVE;
                WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);
                ReadFile(hPipe, &packet, sizeof(PipePacket), &bytesRead, NULL);

                if (packet.success) {
                    cout << "Changes saved successfully." << endl;
                }
                else {
                    cout << "Failed to save changes." << endl;
                }
            }
            else {
                cout << "Modifications cancelled locally." << endl;
            }
        }

        cout << "Press Enter to release the record...";
        cin.ignore();
        cin.get();

        packet.cmd = CMD_RELEASE;
        WriteFile(hPipe, &packet, sizeof(PipePacket), &bytesWritten, NULL);
        ReadFile(hPipe, &packet, sizeof(PipePacket), &bytesRead, NULL);
    }

    CloseHandle(hPipe);
    return 0;
}
