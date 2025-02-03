#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int x, y, a, b;
	cout << "Введите ширину 1 прямоугольника" << endl;
	cin >> x;
	cout << "Введите длинну 1 прямоугольника" << endl;
	cin >> y;
	cout << "Введите ширину 2 прямоугольника" << endl;
	cin >> a;
	cout << "Введите длинну 2 прямоугольника" << endl;
	cin >> b;
	if (x < a && y < b)
		cout << "Можно во 2 поместить 1";
	else if (x < b && y < a)
			cout << "Можно во 2 поместить 1";
	else if (a < x && b < y)
			cout << "Можно в 1 поместить 2";
	else if (a < y && b < x)
			cout << "Можно в 1 поместить 2";
	else cout << "Нельзя";
	return 0;
}
