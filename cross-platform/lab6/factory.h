#pragma once
#include <iostream>
using namespace std;
enum EquationID {LinearEquationID = 1, QwadricEquationID};
class Equation {
public:
	virtual void solve(ostream& os) = 0;
	virtual void print(ostream& os) const = 0;
	virtual bool hasSolution() const = 0;
	virtual bool hasInfiniteSolutions() const = 0;
	virtual double getLeadingCoefficient() const = 0;
	virtual ~Equation() = default;
	static Equation* CreateEquation(EquationID id, const double a, const double b, const double c);
};

class QwadricEquation : public Equation {
private:
	double a, b, c;
public: 
	QwadricEquation(double a, double b, double c);
	void solve(ostream& os) override;
	bool hasSolution() const override;
	bool Determinant() const;
	bool isSquare() const;
	bool hasInfiniteSolutions() const override;
	double getLeadingCoefficient() const override;
	void print(ostream& os) const override;
};
class LinearEquation : public Equation {
private:
	double a, b;
public:
	LinearEquation(double a, double b) : a(a), b(b) {}
	void solve(ostream& os) override;
	bool hasSolution() const override;
	bool hasInfiniteSolutions() const override;
	double getLeadingCoefficient() const override;
	double getSecondCoefficient() const;
	void print(ostream& os) const override;
};
// Фабрики объектов 
class Factory
{
public:
	virtual Equation* CreateEquation(const int a, const int b, const int c) = 0;
	virtual ~Factory() {}
};
class LinearEquationFactory : public Factory {
public:
	Equation* CreateEquation(const int a, const int b, const int c) override {
		return new LinearEquation(a, b);
	}
};
class QwadricEquationFactory : public Factory {
public:
	Equation* CreateEquation(const int a, const int b, const int c) override {
		return new QwadricEquation(a, b, c);
	}
};