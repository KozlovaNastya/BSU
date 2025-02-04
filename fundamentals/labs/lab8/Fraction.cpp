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
		throw DivByZeroException("Divide by 0 error!");
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

Fraction Fraction::operator - () const {
	return Fraction(-n, d);
}

Fraction Fraction::operator !() const {
	return Fraction(d, n);
}

Fraction Fraction::operator ++ () {
	return Fraction(n + d, d);
}

Fraction Fraction::operator ++ (int) {
	Fraction temp = *this;
	n += d;
	return temp;
}

Fraction& Fraction::operator = (const Fraction& other) {
	if (this != &other) {
		n = other.n;
		d = other.d;
	}
	return *this;
}

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
		throw DivByZeroException("Divide by 0 error!");
	}
		n = n * other.d;
		d = d * other.n;
	return *this;
}

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
		throw DivByZeroException("Divide by 0 error!");
	}
	return Fraction(n * other.d, d * other.n);
}

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

Fraction::operator double() {
	return double(n) / d;
}
double Fraction::value() const {
	return static_cast<double>(n) / d;
}

ostream& operator << (ostream& so, const Fraction& other) {
	if (other.getDenom() == 0)
		so << "Divide by 0 error!" << endl;
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

istream& operator >> (istream& is, Fraction& other) {
	char del;
	int n, d;
	is >> n >> del >> d;
	if (d == 0) {
		cerr << "The denominator cannot be zero. d=1 will be assigned for correct operation of the program." << endl;
		d = 1;
	}
	other.n = n;
	other.d = d;
	return is;
}
