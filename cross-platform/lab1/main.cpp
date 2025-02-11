#include <iostream>
#include "Bank.h"
#include <exception>
using namespace std;
int main() {
	try {
	Money bablo(2, 120, 4);
	Money bablo1 = bablo;
	Money a(1, 1, 1);
	Money b(3, 2, 4);
	cout << bablo << endl;
	a += b;
	cout << a << endl;
	a -= b;
	cout << a << endl;
	cout << bablo1 << endl;
	cout << -bablo << endl;
	Money bablo2(0, 6, 2);
	cout << -bablo2 << endl;;
	bablo2 = bablo + bablo1;
	cout << bablo2 << endl;
	bablo2 = bablo - bablo1;
	cout << bablo2 << endl;
	Money bablo4(11, 19, 11);

	Money bablo3(1, 1, 1);
	cout << bablo3 + bablo4 << endl;


	cout << (bablo3 == bablo) << endl;
	cout << (bablo3 < bablo) << endl;
	}
	catch (const exc& e) {
		cerr << e.what() << endl;
	}
	return 0;
}