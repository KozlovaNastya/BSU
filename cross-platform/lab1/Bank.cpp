#include "Bank.h"
#include <iostream>
#include <exception>
using namespace std;
const char* exc::what() const noexcept {
	return message.c_str();
}
Money::Money(int pdd, int shh, int pp) : pd(pdd), sh(shh), p(pp) {
	if (sh >= 20)
		throw exc("sh >= 20");
	if (p >= 12)
		throw exc("p >= 12");
	if (pd > 1'000'000'000) {
			throw exc("pd > 1'000'000'000");
	}
};

int Money::getPd() const { return pd; };
int Money::getSh() const { return sh; };
int Money::getP() const { return p; };
void Money::setPd(int pdd) { p = pdd; };
void Money::setSh(int shh) { sh = shh; };
void Money::setP(int pp) { p = pp; };

Money& Money::operator = (const Money& other) {
	this->pd = other.pd;
	this->sh = other.sh;
	this->p = other.p;
	return *this;
};
Money Money::operator - () const {
	if (pd != 0)
		return Money(-pd, sh, p);
	else if (sh != 0)
		return Money(pd, -sh, p);
	else if (p != 0)
		return Money(pd, sh, -p);
	else return Money(pd, sh, p);
};
Money Money::operator + (const Money& other) const {
	Money temp;
	temp.pd = this->pd + other.pd;
	temp.sh = this->sh + other.sh;
	temp.p = this->p + other.p;
	if (temp.p >= 12) {
		temp.p -= 12;
		temp.sh += 1;
	}
	if (temp.sh >= 20) {
		temp.sh -= 20;
		temp.pd += 1;
	}
	if (temp.pd > 1'000'000'000) {
		throw exc("pd > 1'000'000'000");
	}
	return temp;
};
Money Money::operator - (const Money& other) const {
	Money temp;
	temp.pd = this->pd - other.pd;
	temp.sh = this->sh - other.sh;
	temp.p = this->p - other.p;
	if (temp.p <= 0) {
		temp.p += 12;
		temp.sh -= 1;
	}
	if (temp.sh < 0) {
		temp.sh += 20;
		temp.pd -= 1;
	}
	if (temp.pd < -1'000'000'000) {
		throw exc("pd < -1'000'000'000");
	}
	return temp;
};
Money& Money::operator += (const Money& other) {
	*this = *this + other;
	return *this;
};
Money& Money::operator -= (const Money& other) {
	*this = *this - other;
	return *this;
};
bool Money::operator == (const Money& other) const {
	if (pd == other.pd && sh == other.sh && p == other.p)
		return true;
	else return false;

};
bool Money::operator < (const Money& other) const {
	if (pd < other.pd) return true;
	if (pd > other.pd) return false;
	if (sh < other.sh) return true;
	if (sh > other.sh) return false;
	return p < other.p;
};
ostream& operator << (ostream& os, const Money& other) {
	if (other.pd != 0)
		os << other.pd << "pd.";
	if (other.sh != 0)
		os << other.sh << "sh.";
	if (other.p != 0)
		os << other.p << "p.";
	if (other.pd == 0 && other.sh == 0 && other.p == 0)
		os << "0p.";
	return os;
};