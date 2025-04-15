#include "composite.h"
QwadricEquation::QwadricEquation(double a, double b, double c) : a(a), b(b), c(c) {
	if (a == 0) throw invalid_argument("Error: this is not qwadric equation");
}
void QwadricEquation::solve(ostream& os){
	double D = b * b - 4 * a * c;
	if (D < 0) os << "no real solutions" << endl;
	else if (D == 0) os << "solution: x = " << -b / (2 * a) << endl;
	else {
		os << "first solution: x1 = " << (-b + sqrt(D)) / (2 * a) << endl << "second solution: x2 = " << (-b - sqrt(D)) / (2 * a) << endl;
	}
}
bool QwadricEquation::hasSolution() const{
	return (b * b - 4 * a * c) >= 0;
}
bool QwadricEquation::Determinant() const {
	return (b * b - 4 * a * c) < 0;
}
bool QwadricEquation::isSquare() const {
	if (b * b - 4 * a * c != 0) return false;
	double p = sqrt(a);
	double q = b / (2 * p);
	return (p * p == a) && (2 * p * q == b) && (q * q == c);
}
bool QwadricEquation::hasInfiniteSolutions() const {
	return false;
}
double QwadricEquation::getLeadingCoefficient() const {
	return a;
}
void QwadricEquation::print(ostream& os) const {
	os << a << "x^2 ";
	if (b != 0) os << (b > 0 ? "+ " : "- ") << abs(b) << "x ";
	if (c != 0) os << (c > 0 ? "+ " : "- ") << abs(c) << " ";
	os << "= 0" << endl;
}
void LinearEquation::solve(ostream& os) {
	if (a == 0) {
		if (b == 0) os << "infinite number of solutions" << endl;
		else os << "no solutions" << endl;
	}
	else os << "solution: x = " << -b / a << endl;
}
bool LinearEquation::hasSolution() const {
	return !(a == 0 && b != 0);
}
bool LinearEquation::hasInfiniteSolutions() const {
	return (a == 0 && b == 0);
}
double LinearEquation::getLeadingCoefficient() const {
	return a;
}
double LinearEquation::getSecondCoefficient() const {
	return b;
}
void LinearEquation::print(ostream& os) const {
	os << a << "x ";
	if (b != 0) os << (b > 0 ? "+ " : "- ") << abs(b) << " ";
	os << "= 0" << endl;
}
void CompositeEquation::solve(ostream& os) {
	for (Equation* eq : c) {
		eq->print(os);
		eq->solve(os);
		os << endl;
	}
}
void CompositeEquation::print(ostream& os) const {
	for (Equation* eq : c) {
		eq->print(os);
	}
}
bool CompositeEquation::hasSolution() const {
	for (Equation* eq : c) {
		if (!eq->hasSolution())
			return false;
	}
	return true;
}
bool CompositeEquation::hasInfiniteSolutions() const {
	for (Equation* eq : c) {
		if (!eq->hasInfiniteSolutions())
			return false;
	}
	return true;
}
double CompositeEquation::getLeadingCoefficient() const {
	double total = 0;
	for (int i = 0; i < c.size(); ++i)
		total += c[i]->getLeadingCoefficient();
	return total;
}
void CompositeEquation::addEquation(Equation* eq) {
	c.push_back(eq);
}
CompositeEquation::~CompositeEquation() {
	for (int i = 0; i < c.size(); i++)
		delete c[i];
}