#include <iostream>
#include <iomanip>
#include "Main.h"

using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	float e, x, sum;
	cout << "Enter x and limit" << endl;
	cin >> x >> e;
	if (x > -1 && x < 1) {
		sum = Function(e, x) - Log1(x);
		cout << fixed << setprecision(10) << Function(e, x) << endl << fixed << setprecision(10) << Log1(x) << endl;
		cout << "The sum of the own function differs from the sum of the standard function by" << endl << sum;
	}
	else cout << "Incorrectly entered data";
	return 0;
}
