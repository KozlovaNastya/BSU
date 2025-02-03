#include <iostream>
#include <fstream>
using namespace std;
int main() {
	ifstream in1("f1.txt");
	ifstream in2("f2.txt");
	fstream out("fout.txt");
	if (!in1.is_open()) {
		cerr << "f1 is ERROR";
		return 1;
	}
	if (!in2.is_open()) {
		cerr << "f2 is ERROR";
		return 1;
	}
	if (!out.is_open()) {
		cerr << "fout is ERROR";
		return 1;
	}
	int n1, n2;
	if (in1 >> n1) {
	}
	else {
		n1 = INT_FAST32_MAX;
	}
	if (in2 >> n2) {
	}
	else {
		n2 = INT_FAST32_MAX;
	}
	while (n1 != INT_FAST32_MAX || n2 != INT_FAST32_MAX) {
		if (n1 > n2) {
			out << n2 << " ";
			if (!(out >> n2)) {
				n2 = INT_FAST32_MAX;
			}
		}
		else {
			out << n1 << " ";
			if (!(in1 >> n1)) {
				n1 = INT_FAST32_MAX;
			}
		}
	}
	in1.close();
	in2.close();
	out.close();
	return 0;
}
