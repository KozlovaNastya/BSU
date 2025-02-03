#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;
int main() {
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
	string line;
	int count = 0;
	bool letters[26] = { false };
	while (getline(input, line)){
		for (char symbol : line) {
			if (isalpha(symbol)) {
				int index = tolower(symbol) - 'a';
				if (index < 26 && index >= 0) {
					if (!letters[index]) {
						letters[index] = true;
						count++;
					}
				}
			}
		}
	}
	output << count << endl;
	for (int i = 0; i < 26; i++) {
		if (letters[i] == true)
			output << static_cast<char>(i + 'a') << ' ';
	}
	input.close();
	output.close();
	return 0;
}
