#include <iostream>
#include <fstream>
#include <string>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: Creator.exe [filename] [count]" << std::endl;
        return 1;
    }

    char* fileName = argv[1];
    int count = std::stoi(argv[2]);

    std::ofstream out(fileName, std::ios::binary);
    if (!out) {
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        employee emp;
        std::cout << "Employee " << i + 1 << " (ID, Name, Hours): ";
        std::cin >> emp.num >> emp.name >> emp.hours;

        out.write((char*)&emp, sizeof(employee));
    }

    out.close();
    return 0;
}
