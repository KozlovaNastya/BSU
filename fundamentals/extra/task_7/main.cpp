#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int f2, f1, f, i, n;
	cout << "Enter the number of repetitions\n";
	cin >> n;
	f = 1;
	f1 = f;
	cout << "1\n1\n";
	for (i = 0; i < n-2; i++) {
		f2 = f1;
		f1 = f + f1;
		f = f2;
		cout << f1 << endl;
	}
	return 0;
}
