#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int a, r;
	cout << "Enter the side of the square\n";
	cin >> a;
	cout << "Enter the radius of the circle\n";
	cin >> r;
	if (a <= r * sqrt(2))
		cout << "Possible";
	else cout << "Impossible";
	return 0;
}
