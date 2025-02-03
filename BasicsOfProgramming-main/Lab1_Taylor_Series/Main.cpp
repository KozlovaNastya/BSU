#include <iostream>
#include <iomanip>
#include "Main.h"

using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	float e, x, sum;
	cout << "Введите х и предел" << endl;
	cin >> x >> e;
	if (x > -1 && x < 1) {
		sum = Function(e, x) - Log1(x);
		cout << fixed << setprecision(10) << Function(e, x) << endl << fixed << setprecision(10) << Log1(x) << endl;
		cout << "Сумма по собственной функции отличается от суммы по стандартной функции на" << endl << sum;
	}
	else cout << "Неверно введенные данные";
	return 0;
}
