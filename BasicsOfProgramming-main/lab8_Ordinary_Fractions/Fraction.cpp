#include "Fraction.h"
#include <iostream>
#include <exception>
using namespace std;
int Fraction::countID = 2;
const char* DivByZeroException::what() const noexcept {
	return message.c_str();
}
Fraction::Fraction(int n, int d) : n(n), d(d), ID{ countID++ } {
	if (d == 0)
		throw DivByZeroException("Ошибка деление на ноль!");
	simplify();
}
int Fraction::nod(int a, int b) {
	int temp;
	while (b != 0) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
};
void Fraction::simplify() {
	int comon = nod(n, d);
	if (comon != 1) {
		n /= comon;
		d /= comon;
	}
	if (d < 0) {
		n = -n;
		d = -d;
	}
};

int Fraction::getID() const { return ID; };
int Fraction::getNum() const { return n; }
int Fraction::getDenom() const { return d; }
void Fraction::setNum(int nn) { n = nn; };
void Fraction::setDenom(int dd) { d = dd; };

//Унарный минус
Fraction Fraction::operator - () const {
	return Fraction(-n, d);
}

//Обратная дробь
Fraction Fraction::operator !() const {
	return Fraction(d, n);
}

//Префиксный инкремент
Fraction Fraction::operator ++ () {
	return Fraction(n + d, d);
}

//Постфиксный инкремент
Fraction Fraction::operator ++ (int) {
	Fraction temp = *this;
	n += d;
	return temp;
}

//Оператор присваивания
Fraction& Fraction::operator = (const Fraction& other) {
	if (this != &other) {
		n = other.n;
		d = other.d;
	}
	return *this;
}

//Составные операторы присваивания
Fraction& Fraction::operator += (const Fraction& other) {
	if (this != &other) {
		n = n * other.d + d * other.n;
		d = d * other.d;
	}
	return *this;
}
Fraction& Fraction::operator -= (const Fraction& other) {
	if (this != &other) {
		n = n * other.d - d * other.n;
		d = d * other.d;
	}
	return *this;
}
Fraction& Fraction::operator *= (const Fraction& other) {
	if (this != &other) {
		n = n * other.n;
		d = d * other.d;
	}
	return *this;
}
Fraction& Fraction::operator /= (const Fraction& other) {
	if (this != &other && other.n == 0) {
		throw DivByZeroException("Ошибка деление на ноль!");
	}
		n = n * other.d;
		d = d * other.n;
	return *this;
}

//Составные операторы присваивания c числом
Fraction& Fraction::operator += (int other) {
	n = n + d * other;
	d = d;
	return *this;
}
Fraction& Fraction::operator -= (int other) {
	n = n - d * other;
	d = d;
	return *this;
}
Fraction& Fraction::operator *= (int other) {
	n = n * other;
	d = d;
	return *this;
}
Fraction& Fraction::operator /= (int other) {
	n = n;
	d = d * other;
	return *this;
}

//Сложение с числом справа
Fraction Fraction::operator + (int other) const {
	return Fraction(n + d * other, d);
}
Fraction Fraction::operator - (int other) const {
	return Fraction(n - d * other, d);
}
Fraction Fraction::operator * (int other) const {
	return Fraction(n * other, d);
}
Fraction Fraction::operator / (int other) const {
	return Fraction(n, d * other);
}

//сложение с числом слева
Fraction operator+ (int number, const Fraction& other) {
	return Fraction(number * other.d + other.n, other.d);
}
Fraction operator- (int number, const Fraction& other) {
	return Fraction(number * other.d - other.n, other.d);
}
Fraction operator* (int number, const Fraction& other) {
	return Fraction(number * other.n, other.d);
}
Fraction operator/ (int number, const Fraction& other) {
	return Fraction(number * other.d, other.n);
}

//Бинарные операции
Fraction Fraction::operator+ (const Fraction& other) const {
	return Fraction(n * other.d + other.n * d, d * other.d);
}
Fraction Fraction::operator- (const Fraction& other) const {
	return Fraction(n * other.d - other.n * d, d * other.d);
}
Fraction Fraction::operator* (const Fraction& other) const {
	return Fraction(n * other.n, d * other.d);
}
Fraction Fraction::operator/ (const Fraction& other) const {
	if (other.n == 0) {
		throw DivByZeroException("Ошибка деление на ноль!");
	}
	return Fraction(n * other.d, d * other.n);
}

//Сравнение
bool Fraction::operator == (const Fraction& other) const {
	return (n * other.d == other.n * d);
}
bool Fraction::operator <= (const Fraction& other) const {
	return (n * other.d <= other.n * d);
}
bool Fraction::operator < (const Fraction& other) const {
	return (n * other.d < other.n * d);
}
bool Fraction::operator >= (const Fraction& other) const {
	return (n * other.d >= other.n * d);
}
bool Fraction::operator > (const Fraction& other) const {
	return (n * other.d > other.n * d);
}

//Превращение обыкновенной дроби в десятичную
Fraction::operator double() {
	return double(n) / d;
}
double Fraction::value() const {
	return static_cast<double>(n) / d;
}
//Перегрузка оператора вывода
ostream& operator << (ostream& so, const Fraction& other) {
	if (other.getDenom() == 0)
		so << "Ошибка: деление на ноль!" << endl;
	else if (other.getNum() == 0)
		so << 0 << endl;
	else if (other.getNum() == other.getDenom())
		so << 1 << endl;
	else if (other.getDenom() == 1)
		so << other.getNum() << endl;
	else
		so << other.getNum() << '/' << other.getDenom() << endl;
	return so;
}

//Перегрузка оператора ввода
istream& operator >> (istream& is, Fraction& other) {
	char del;
	int n, d;
	is >> n >> del >> d;
	if (d == 0) {
		cerr << "Ошибка деление на ноль!!! Будет присвоено d = 1 для корректой работы" << endl;
		d = 1;
	}
	other.n = n;
	other.d = d;
	return is;
}