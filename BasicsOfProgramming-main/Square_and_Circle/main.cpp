#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int a, r;
	cout << "Введите сторону квадрата\n";
	cin >> a;
	cout << "Введите радиус окружности\n";
	cin >> r;
	if (a <= r * sqrt(2))
		cout << "Можно поместить";
	else cout << "Нельзя поместить";
	return 0;
}
