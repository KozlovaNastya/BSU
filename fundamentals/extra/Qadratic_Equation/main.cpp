#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int a, b, c, D, x1, x2;
	cout << "Введите a\n";
	cin >> a;
	cout << "Введите b\n";
	cin >> b;
	cout << "Введите с\n";
	cin >> c;
	D = b * b - 4 * a * c;
	if (D > 0) {
		x1 = (-b + sqrt(D)) / 2 * a;
		x2 = (-b - sqrt(D)) / 2 * a;
		cout << "x1 = " << x1 << "\nx2 = " << x2;
	}
	if (D < 0)
		cout << "Решений нет";
	if (D == 0) {
		x1 = (-b / 2 * a);
		cout << "x = " << x1;
	}
	return 0;
}
