#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main() {
    std::string binFileName;
    int recordsCount;

    std::cout << "Enter binary file name: ";
    std::cin >> binFileName;
    std::cout << "Enter number of records: ";
    std::cin >> recordsCount;

    std::string cmdLine = "Creator.exe " + binFileName + " " + std::to_string(recordsCount);
    std::wstring wCmdLine(cmdLine.begin(), cmdLine.end());

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, &wCmdLine[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cout << "Error: Could not launch Creator.exe. Code: " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::ifstream in(binFileName, std::ios::binary);
    employee temp;
    std::cout << "\nContent of " << binFileName << ":" << std::endl;
    while (in.read((char*)&temp, sizeof(employee))) {
        std::cout << temp.num << " " << temp.name << " " << temp.hours << std::endl;
    }
    in.close();

    std::string reportFileName;
    double hourlyRate;

    std::cout << "\nEnter report file name: ";
    std::cin >> reportFileName;
    std::cout << "Enter hourly rate: ";
    std::cin >> hourlyRate;

    std::string cmdLineRep = "Reporter.exe " + binFileName + " " + reportFileName + " " + std::to_string(hourlyRate);
    std::wstring wCmdLineRep(cmdLineRep.begin(), cmdLineRep.end());

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, &wCmdLineRep[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cout << "Error: Could not launch Reporter.exe" << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "\n--- Final Report ---\n";
    std::ifstream reportIn(reportFileName);
    std::string line;
    while (std::getline(reportIn, line)) {
        std::cout << line << std::endl;
    }
    reportIn.close();

    std::cout << "\nWork completed." << std::endl;

    return 0;
}
