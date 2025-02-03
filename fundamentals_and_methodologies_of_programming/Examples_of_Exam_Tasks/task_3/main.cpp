#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream input("input.txt");
	ofstream output("output.txt");
	if (!output.is_open()) {
		cerr << "ERROR with open output file";
		return 1;
	}
	if (!input.is_open()) {
		cerr << "ERROR with open intput file";
		return 1;
	}
	if (input.peek() == EOF) {
		cerr << "input file is empty";
		return 1;
	}
	string poisk, zamena, line;
	getline(input, poisk, '.');
	getline(input, zamena);
	while (getline(input, line)) {
		int pos = line.find(poisk);
		if (pos == string::npos) {
			output << line << endl;
		}
		else {
			int start = 0;
			while (pos < line.length()) {
				line.replace(pos, poisk.length(), zamena);
				pos += poisk.length();
				pos = line.find(poisk, pos);
			}
			output << line << endl;
		}
	}
	input.close();
	output.close();
	return 0;
}
