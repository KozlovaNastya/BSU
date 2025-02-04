#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int x, y, a, b;
	cout << "Enter the width of 1 rectangle" << endl;
	cin >> x;
	cout << "Enter the length of 1 rectangle" << endl;
	cin >> y;
	cout << "Enter a width of 2 rectangles" << endl;
	cin >> a;
	cout << "Enter the length of 2 rectangles" << endl;
	cin >> b;
	if (x < a && y < b)
		cout << "You can put 1 in 2";
	else if (x < b && y < a)
			cout << "You can put 1 in 2";
	else if (a < x && b < y)
			cout << "You can put 2 in 1";
	else if (a < y && b < x)
			cout << "You can put 2 in 1";
	else cout << "Impossible";
	return 0;
}
