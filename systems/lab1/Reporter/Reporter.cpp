#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: Reporter.exe [input_bin] [output_txt] [salary_per_hour]" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    double salaryPerHour = std::stod(argv[3]);

    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error opening binary file!" << std::endl;
        return 1;
    }

    std::ofstream out(outputFile);
    if (!out) {
        std::cerr << "Error creating report file!" << std::endl;
        return 1;
    }

    out << "Report on file «" << inputFile << "»" << std::endl;
    out << "ID, name, hours, sellary" << std::endl;

    employee emp;
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double totalSalary = emp.hours * salaryPerHour;

        out << emp.num << ", "
            << emp.name << ", "
            << emp.hours << ", "
            << std::fixed << std::setprecision(2) << totalSalary << std::endl;
    }

    in.close();
    out.close();
    return 0;
}
