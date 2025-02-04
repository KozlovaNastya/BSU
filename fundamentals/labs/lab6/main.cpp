#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool Proverka(const string& subline) { 
	for (int i = 1; i < subline.length(); i++) {
		if (subline[i - 1] >= subline[i])
			return false;
	}
	return true;
}
string MaxsubLine(const string& line) { 
	string subline;
	string maxsubline;
	int pos = 0;
	while (pos < line.length()) {
		size_t space = line.find(' ', pos);
		if (space == string::npos)
			space = line.length();
		subline = line.substr(pos, space - pos);
		pos = space + 1;
		if (Proverka(subline) && maxsubline.length() < subline.length())
				maxsubline = subline;
		}
	return maxsubline;
}
int main() {
	setlocale(LC_ALL, ".1251");
	ifstream in("input.txt");
	if (!in.is_open()) {
		cerr << "ERROR with input.txt";
		return 1;
	}
	string line;
	int count = 0;
	while (getline(in, line) && count < 10) {
		string subline = MaxsubLine(line);
		if (!subline.empty())
			cout << ++count << ". Maximum strictly increasing substring: " << subline << endl << "In line: " << line << endl << endl;
	}
	in.close();
	return 0;
}
