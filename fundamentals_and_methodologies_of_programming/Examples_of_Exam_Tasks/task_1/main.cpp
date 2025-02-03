#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
//#include <cstdlib>
//#include <ctime>
//srand(time(nullptr)); rand() % (x + 1) - 10;
using namespace std;
int sum(int a) {
	int sum = 0;
	a = abs(a);
	while (a > 0) {
		sum += a % 10;
		a /= 10;
	}
	return sum;
}
void sort(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (sum(array[j]) < sum(array[minIndex])) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swap(array[i], array[minIndex]);
		}
	}
}
int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");
	if (!output.is_open()) {
		cerr << "ERROR with open output file";
		return 1;
	}
	if (!input.is_open()) {
		cerr << "ERROR with open input file";
		return 1;
	}
	if (input.peek() == EOF) {
		cerr << "input file is empty";
		return 1;
	}
	int n, x, y;
	input >> n;
	if (n <= 0 || n > 20) {
		cerr << "n is not correct number";
		return 1;
	}
	input >> x >> y;
	if (!(input >> n >> x >> y)) {
		cerr << "Invalid input format";
		return 1;
	}
	if (x > y) {
		cerr << "Invalid range: X should be less than or equal to Y";
		return 1;
	}
	int array[20] = { 0 };
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(x, y);
	for (int i = 0; i < n; i++) {
		array[i] = dis(gen);
	}
	for (int i = 0; i < n; i++) {
		output << array[i] << ' ';
	}
	sort(array, n);
	output << endl << "Sorted:" << endl;
	for (int i = 0; i < n; i++) {
		output << array[i] << ' ';
	}
	return 0;
}
