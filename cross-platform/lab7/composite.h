#pragma once
#include <iostream>
#include <vector>
using namespace std;
enum EquationID {LinearEquationID = 1, QwadricEquationID};
class Equation {
public:
	virtual void solve(ostream& os) = 0;
	virtual void print(ostream& os) const = 0;
	virtual bool hasSolution() const = 0;
	virtual bool hasInfiniteSolutions() const = 0;
	virtual double getLeadingCoefficient() const = 0; //вот ее будем
	virtual ~Equation() = default;
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
	virtual double getLeadingCoefficient() const;
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
	virtual double getLeadingCoefficient() const;
	double getSecondCoefficient() const;
	void print(ostream& os) const override;
};
//Composite
class CompositeEquation : public Equation {
private:
		vector<Equation*> c;
public:
	void addEquation(Equation* eq);
	void solve(ostream& os) override;
	void print(ostream& os) const override;
	bool hasSolution() const override;
	bool hasInfiniteSolutions() const override;
	double getLeadingCoefficient() const;
	~CompositeEquation();
};