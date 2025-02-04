#ifndef FRACTION_H // Защита от повторного включения
#define FRACTION_H
#include <iostream>
#include <exception>
class DivByZeroException : public std::exception {
private:
	std::string message;
public:
	DivByZeroException(const std::string& msg) : message(msg) {}
	const char* what() const noexcept override;
};
class Fraction {
private:
	int n, d;
	const int ID;
	static int countID;
	int nod(int a, int b);
	void simplify();

public:
	Fraction(int n = 0, int d = 1);

	int getID() const;
	int getNum() const;
	int getDenom() const;
	void setNum(int nn);
	void setDenom(int dd);

	Fraction operator - () const;
	Fraction operator !() const;
	Fraction operator ++ ();
	Fraction operator ++ (int);
	Fraction& operator = (const Fraction& other);
	Fraction& operator += (const Fraction& other);
	Fraction& operator -= (const Fraction& other);
	Fraction& operator *= (const Fraction& other);
	Fraction& operator /= (const Fraction& other);
	Fraction& operator += (int other);
	Fraction& operator -= (int other);
	Fraction& operator *= (int other);
	Fraction& operator /= (int other);
	Fraction operator + (int other) const;
	Fraction operator - (int other) const;
	Fraction operator * (int other) const;
	Fraction operator / (int other) const;
	friend Fraction operator+ (int number, const Fraction& other);
	friend Fraction operator- (int number, const Fraction& other);
	friend Fraction operator* (int number, const Fraction& other);
	friend Fraction operator/ (int number, const Fraction& other);
	Fraction operator+ (const Fraction& other) const;
	Fraction operator- (const Fraction& other) const;
	Fraction operator* (const Fraction& other) const;
	Fraction operator/ (const Fraction& other) const;
	bool operator == (const Fraction& other) const;
	bool operator <= (const Fraction& other) const;
	bool operator < (const Fraction& other) const;
	bool operator >= (const Fraction& other) const;
	bool operator > (const Fraction& other) const;
	operator double();
	double value() const;
	friend std::ostream& operator << (std::ostream& os, const Fraction& other);
	friend std::istream& operator >> (std::istream& is, Fraction& other);
};
#endif