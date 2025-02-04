#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
bool palindrom(string word) {
	for (int i = 0; i < word.length() / 2; i++) {
		if (word[i] != word[word.length() - 1 - i])
			return false;
	}
	return true;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream input("input.txt");
	if (!input) {
		cerr << "ERROR with input file";
		return 1;
	}
	if (input.peek() == EOF) {
		cerr << "input is empty";
		return 1;
	}
	ofstream output("output.txt");
	if (!output) {
		cerr << "ERROR with output file";
		return 1;
	}
	string separators, line;
	getline(input, separators);
	while (getline(input, line)) {
		bool flag = false;
		int start = 0, pos = 0;
		while (pos <= line.length()) {
			string word;
			pos = line.find_first_of(separators, start);
			int length = (pos == string::npos) ? line.length() - start : pos - start;
			if (length > 0) {
				word = line.substr(start, length);
				if (palindrom(word)) {
					output << word << ' ';
					flag = true;
				}
			}
			start = (pos == string::npos) ? line.length() : pos + 1;
		}
		if (!flag) {
			output << "there is no palindromes";
		}
		output << endl;
	}
	input.close();
	output.close();
	return 0;
}
