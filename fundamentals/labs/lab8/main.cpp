#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <ctime>
#include "Fraction.h"
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(0));
	vector<Fraction> fractions;
	for (int i = 0; i < 4; i++) {
		int n = -2 + rand() % 5;
		int d = -2 + rand() % 5;
		if (d == 0)
			d = 1;
		fractions.emplace_back(n, d);
	}
	int predN = 1, predD = 1;
	for (const Fraction& frac : fractions) {
		predN *= frac.getNum();
		predD *= frac.getDenom();
	}
	fractions.emplace_back(predN, predD);
	for (int i = 4; i < 6; i++) {
		int predID = fractions[i - 1].getID();
		double predValue = fractions[i - 1].value();
		fractions.emplace_back((predID + static_cast<int>(predValue)), 1);
	}
	double sum = 0;
	int count = 0;
	for (const Fraction& frac : fractions) {
		if (frac.getID() % 2 != 0) {
			sum += frac.value();
			count++;
		}
	}
	double sred = 0;
	if (count != 0)
		sred = sum / count;
	for (const Fraction& frac : fractions)
		cout <<"ID: " << frac.getID() << " Element: " << frac;
	cout << "Average: " << sred << endl << endl;

//------------------------------------------
	cout << "Demonstration of class methods" << endl;
	Fraction drob1;
	Fraction drob2;
	cout << "Enter fractions as follows: 1/3" << endl;
	try {
		cout << "Enter drob1: ";
		cin >> drob1;
	}
	catch (const DivByZeroException& e) {
		cerr << e.what() << endl;
	}
	try {
		cout << "Enter brob2: ";
		cin >> drob2;
	}
	catch (const DivByZeroException& e) {
		cerr << e.what() << endl;
	}

//Вывод результата
	Fraction result;
	bool proverka;

	cout << "Add drob1 + drob2: " << endl;
	cout << drob1 + drob2;
	cout << "Subtract drob1 - drob2: " << endl;
	cout << drob1 - drob2;
	cout << "Multiply drob1 * drob2: " << endl;
	cout << drob1 * drob2;
	try {
		cout << "Divide drob1 / drob2: " << endl;
		cout << drob1 / drob2;
	}
	catch (const DivByZeroException& e) {
		cerr << e.what() << endl;
	}
	cout << "Unary minus for drob1: " << endl;
	cout << -drob1;
	cout << "Reverse drob1: " << endl;
	cout << !drob1;
	cout << "Operation += with number 3 and drob2: " << endl;
	cout << (drob2 += 3);
	cout << "Operation -= with number 3 and drob2: " << endl;
	cout << (drob2 -= 3);
	cout << "Operation *= with number 3 and drob2: " << endl;
	cout << (drob2 *= 3);
	cout << "Operation /= with number 3 and drob2: " << endl;
	cout << (drob2 /= 3);
	cout << "Addition with number 3 on the right and drob1: " << endl;
	cout << (drob1 + 3);
	cout << "Subtraction with the number 3 on the right and drob1: " << endl;
	cout << (drob1 - 3);
	cout << "Multiplication with number 3 on the right and drob1: " << endl;
	cout << (drob1 * 3);
	cout << "Division with number 3 on the right and drob1: " << endl;
	cout << (drob1 / 3);
	cout << "Addition with number 3 on the left and drob1: " << endl;
	cout << (3 + drob1);
	cout << "Subtraction with the number 3 on the left and drob1: " << endl;
	cout << (3 - drob1);
	cout << "Multiplication with number 3 on the left and drob1: " << endl;
	cout << (3 * drob1);
	cout << "Division with number 3 on the left and drob1: " << endl;
	cout << (3 / drob1);
	cout << "Prefix increment for drob1: " << endl;
	cout << (++drob1);
	cout << "Postfix increment for drob2: " << endl;
	cout << (drob2++);
	cout << "Assignment operator for first fraction: " << endl;
	cout << (result = drob1);
	cout << "Compound operator += for drob1 and drob2: " << endl;
	cout << (drob2 += drob1);
	cout << "Compound operator -= for drob1 and drob2: " << endl;
	cout << (drob2 -= drob1);
	cout << "Compound operator *= for drob1 and drob2: " << endl;
	cout << (drob2 *= drob1);
	cout << "Compound operator /= for drob1 and drob2: " << endl;
	cout << (drob2 /= drob1);
	cout << "Сравнение drob1 == drob2 = ";
	proverka = drob1 == drob2;
	cout << proverka << endl;
	cout << "Comparison drob1 <= drob2 = ";
	proverka = drob1 <= drob2;
	cout << proverka << endl;
	cout << "Comparison drob1 < drob2 = ";
	proverka = drob1 < drob2;
	cout << proverka << endl;
	cout << "Comparison drob1 >= drob2 = ";
	proverka = drob1 >= drob2;
	cout << proverka << endl;
	cout << "Comparison drob1 > drob2 = ";
	cout << (drob1 > drob2) << endl;
	cout << "Decimal drob1: ";
	cout << double(drob1);
	return 0;
}
