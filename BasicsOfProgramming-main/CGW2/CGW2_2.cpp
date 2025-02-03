#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
struct Student {
    string name;
    int course;
    int group;
};
string getSurname(const string& name) {
    return name.substr(0, name.find(' '));
}
int main() {
    setlocale(LC_ALL, ".1251");
    ifstream inputFile("Students.txt");
    if (!inputFile) {
        cerr << "Не удалось открыть файл Students.txt" << endl;
        return 1;
    }
    if (inputFile.peek() == EOF) {
        cerr << "Файл Student.txt пуст" << endl;
        return 1;
    }
    vector<Student> students;
    string line;
    while (getline(inputFile, line)) {
        Student student;
        student.name = line.substr(0, line.find(';'));
        student.course = stoi(line.substr(line.find(';') + 1, line.rfind(';') - line.find(';') - 1));
        student.group = stoi(line.substr(line.rfind(';') + 1));
        students.push_back(student);
    }
    ofstream outputFile1("Fio.txt");
    ofstream outputFile2("Grops.txt");
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return getSurname(a.name) < getSurname(b.name);
        });
    for (Student stud : students) {
        outputFile1 << stud.name << ';' << stud.course << ';' << stud.group << endl;
    }
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.course != b.course)
            return a.course < b.course;
        if (a.group != b.group)
            return a.group < b.group;
        return getSurname(a.name) < getSurname(b.name);
        });
    for (Student stud : students) {
        outputFile2 << stud.name << ';' << stud.course << ';' << stud.group << endl;
    }
    inputFile.close();
    outputFile1.close();
    outputFile2.close();
	return 0;
}