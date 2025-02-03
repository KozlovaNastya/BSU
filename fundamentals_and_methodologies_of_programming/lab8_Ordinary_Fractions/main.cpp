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
	cout << "Среднее значение: " << sred << endl;

//------------------------------------------
	cout << "Демонстрация методов класса" << endl;
	Fraction drob1;
	Fraction drob2;
	cout << "Вводите дроби следующим образом 1/3" << endl;
	try {
		cout << "Введите drob1: ";
		cin >> drob1;
	}
	catch (const DivByZeroException& e) {
		cerr << e.what() << endl;
	}
	try {
		cout << "Введите brob2: ";
		cin >> drob2;
	}
	catch (const DivByZeroException& e) {
		cerr << e.what() << endl;
	}

//Вывод результата
	Fraction result;
	bool proverka;

	cout << "Сложение drob1 + drob2: " << endl;
	cout << drob1 + drob2;
	cout << "Вычитание drob1 - drob2: " << endl;
	cout << drob1 - drob2;
	cout << "Умножение drob1 * drob2: " << endl;
	cout << drob1 * drob2;
	try {
		cout << "Деление drob1 / drob2: " << endl;
		cout << drob1 / drob2;
	}
	catch (const DivByZeroException& e) {
		cerr << e.what() << endl;
	}
	cout << "Унарный минус для drob1: " << endl;
	cout << -drob1;
	cout << "Обратная drob1: " << endl;
	cout << !drob1;
	cout << "Операция += с числом 3 и drob2: " << endl;
	cout << (drob2 += 3);
	cout << "Операция -= с числом 3 и drob2: " << endl;
	cout << (drob2 -= 3);
	cout << "Операция *= с числом 3 и drob2: " << endl;
	cout << (drob2 *= 3);
	cout << "Операция /= с числом 3 и drob2: " << endl;
	cout << (drob2 /= 3);
	cout << "Сложение c числом 3 справа и drob1: " << endl;
	cout << (drob1 + 3);
	cout << "Вычитание c числом 3 справа и drob1: " << endl;
	cout << (drob1 - 3);
	cout << "Умножение c числом 3 справа и drob1: " << endl;
	cout << (drob1 * 3);
	cout << "Деление c числом 3 справа и drob1: " << endl;
	cout << (drob1 / 3);
	cout << "Сложение c числом 3 слева и drob1: " << endl;
	cout << (3 + drob1);
	cout << "Вычитание c числом 3 слева и drob1: " << endl;
	cout << (3 - drob1);
	cout << "Умножение c числом 3 слева и drob1: " << endl;
	cout << (3 * drob1);
	cout << "Деление c числом 3 слева и drob1: " << endl;
	cout << (3 / drob1);
	cout << "Префиксный инкремент drob1: " << endl;
	cout << (++drob1);
	cout << "Постфиксный инкремент для drob2: " << endl;
	cout << (drob2++);
	cout << "Оператор присваивания для первой дроби: " << endl;
	cout << (result = drob1);
	cout << "Составной оператор += для drob1 и drob2: " << endl;
	cout << (drob2 += drob1);
	cout << "Составной оператор -= для drob1 и drob2: " << endl;
	cout << (drob2 -= drob1);
	cout << "Составной оператор *= для drob1 и drob2: " << endl;
	cout << (drob2 *= drob1);
	cout << "Составной оператор /= для drob1 и drob2: " << endl;
	cout << (drob2 /= drob1);
	cout << "Сравнение drob1 == drob2 = ";
	proverka = drob1 == drob2;
	cout << proverka << endl;
	cout << "Сравнение drob1 <= drob2 = ";
	proverka = drob1 <= drob2;
	cout << proverka << endl;
	cout << "Сравнение drob1 < drob2 = ";
	proverka = drob1 < drob2;
	cout << proverka << endl;
	cout << "Сравнение drob1 >= drob2 = ";
	proverka = drob1 >= drob2;
	cout << proverka << endl;
	cout << "Сравнение drob1 > drob2 = ";
	cout << (drob1 > drob2) << endl;
	cout << "Десятичная drob1: ";
	cout << double(drob1);
	return 0;
}
