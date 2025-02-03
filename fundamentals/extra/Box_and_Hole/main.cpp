#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int a, b, c, x, y;
	cout << "Введите ширину коробки" << endl;
	cin >> a;
	cout << "Введите длинну коробки" << endl;
	cin >> b;
	cout << "Введите высоту коробки" << endl;
	cin >> c;
	cout << "Введите длинну отверстия" << endl;
	cin >> x;
	cout << "Введите ширину отверстия" << endl;
	cin >> y;
	if (a < x && b < y ||
		a < x && c < y || 
		b < x && a < y || 
		b < x && c < y || 
		c < x && a < y || 
		c < x && b < y)
		cout << "Можно";
	else cout << "Нельзя";
	return 0;
}
