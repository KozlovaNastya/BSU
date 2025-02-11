#pragma once
#include <iostream>
#include <exception>
class exc : public std::exception {
private:
	std::string message;
public:
	exc(const std::string& msg) : message(msg) {}
	const char* what() const noexcept override;
};
class Money {
private:
	int pd;
	int sh;
	int p;
public:
	Money(int pdd = 0, int shh = 0, int pp = 0);

	int getPd() const;
	int getSh() const;
	int getP() const;
	void setPd(int pdd);
	void setSh(int shh);
	void setP(int pp);

	Money& operator = (const Money& other);
	Money operator - () const;
	Money operator + (const Money& other) const;
	Money operator - (const Money& other) const;
	Money& operator += (const Money& other);
	Money& operator -= (const Money& other);
	bool operator == (const Money& other) const;
	bool operator < (const Money& other) const;
	friend std::ostream& operator << (std::ostream& os, const Money& other);
};
