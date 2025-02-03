#include <iostream>
#include <fstream>
using namespace std;
int prostoe() {
	static int start = 2;
	int num = start;
	while (true) {
		bool flag = true;
		for (int i = 2; i * i <= num; i++) {
			if (num % i == 0) {
				flag = false;
				break;
			}
		}
		if (flag) {
			start = num + 1;
			return num;
		}
		num++;
	}
}
int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");
	if (!output.is_open()) {
		cerr << "ERROR with open outtput file";
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
	int n;
	input >> n;
	if (input.fail() || n < 3 || n > 100) {
		cerr << "Invalid matrix size in the file.";
		input.close();
		return 1;
	}
	int ** matrix = new int *[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
	int i = 0, j = 0, it = 0;
	while (i < n && j < n) {
		if (it % 2 == 0) {
			for (int i1 = i; i1 < n; i1++) {
				matrix[i1][j] = prostoe();
			}
			j++;
		}
		else {
			for (int j1 = j; j1 < n; j1++) {
				matrix[i][j1] = prostoe();
			}
			i++;
		}
		it++;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) { 
			output << matrix[i][j] << ' ';
		}
		output << endl;
	}
	for (int i = 0; i < n; i++)
		delete [] matrix[i];
	delete [] matrix;
	input.close();
	output.close();
	return 0;
}
