#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int a, b, c, x, y;
	cout << "Enter box width" << endl;
	cin >> a;
	cout << "Enter box length" << endl;
	cin >> b;
	cout << "Enter box height" << endl;
	cin >> c;
	cout << "Enter hole length" << endl;
	cin >> x;
	cout << "Enter hole width" << endl;
	cin >> y;
	if (a < x && b < y ||
		a < x && c < y || 
		b < x && a < y || 
		b < x && c < y || 
		c < x && a < y || 
		c < x && b < y)
		cout << "Possible";
	else cout << "Impossible";
	return 0;
}
