#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int a, b, c, D, x1, x2;
	cout << "Enter a\n";
	cin >> a;
	cout << "Enter b\n";
	cin >> b;
	cout << "Enter с\n";
	cin >> c;
	D = b * b - 4 * a * c;
	if (D > 0) {
		x1 = (-b + sqrt(D)) / 2 * a;
		x2 = (-b - sqrt(D)) / 2 * a;
		cout << "x1 = " << x1 << "\nx2 = " << x2;
	}
	if (D < 0)
		cout << "no solutions";
	if (D == 0) {
		x1 = (-b / 2 * a);
		cout << "x = " << x1;
	}
	return 0;
}
