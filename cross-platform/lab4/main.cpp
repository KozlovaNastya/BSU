#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
class Equation {
public:
	virtual void solve(ostream& os) = 0;
	virtual void print(ostream& os) const = 0;
	virtual bool hasSolution() const = 0;
	virtual bool hasInfiniteSolutions() const = 0;
	virtual double getLeadingCoefficient() const = 0;
	virtual ~Equation() = default;
};
class QwadricEquation : public Equation {
private:
	double a, b, c;
public:
	QwadricEquation(double a, double b, double c): a(a), b(b), c(c){
		if (a == 0) throw invalid_argument("Error: this is not qwadric equation");
	}
	void solve(ostream& os) override {
		double D = b * b - 4 * a * c;
		if (D < 0) os << "no real solutions" << endl;
		else if (D == 0) os << "solution: x = " << -b / (2 * a) << endl;
		else {
			os << "first solution: x1 = " << (-b + sqrt(D)) / (2 * a) << endl << "second solution: x2 = " << (-b - sqrt(D)) / (2 * a) << endl;
		}
	}
	bool hasSolution() const override {
		return (b * b - 4 * a * c) >= 0;
	}
	bool Determinant() const {
		return (b * b - 4 * a * c) < 0;
	}
	bool isSquare() const {
		if (b * b - 4 * a * c != 0) return false;
		double p = sqrt(a);
		double q = b / (2 * p);
		return (p * p == a) && (2 * p * q == b) && (q * q == c);
	}
	bool hasInfiniteSolutions() const override {
		return false;
	}
	double getLeadingCoefficient() const override {
		return a;
	}
	void print(ostream& os) const override {
		os << a << "x^2 ";
		if (b != 0) os << (b > 0 ? "+ " : "- ") << abs(b) << "x ";
		if (c != 0) os << (c > 0 ? "+ " : "- ") << abs(c) << " ";
		os << "= 0" << endl;
	}
};
class LinearEquation : public Equation {
private:
	double a, b;
public:
	LinearEquation(double a, double b) : a(a), b(b){}
	void solve(ostream& os) override {
		if (a == 0) {
			if (b == 0) os << "infinite number of solutions" << endl;
			else os << "no solutions" << endl;
		}
		else os << "solution: x = " << -b / a << endl;
	}
	bool hasSolution() const override {
		return !(a == 0 && b != 0);
	}
	bool hasInfiniteSolutions() const override {
		return (a == 0 && b == 0);
	}
	double getLeadingCoefficient() const override {
		return a;
	}
	double getSecondCoefficient() const {
		return b;
	}
	void print(ostream& os) const override {
		os << a << "x ";
		if (b != 0) os << (b > 0 ? "+ " : "- ") << abs(b) << " ";
		os << "= 0" << endl;
	}
};
bool CompareCoefficients(const shared_ptr<Equation>& eq1, const shared_ptr<Equation>& eq2) {
	return eq1->getLeadingCoefficient() < eq2->getLeadingCoefficient();
}
bool CompareCoefficientAB(const shared_ptr<LinearEquation>& eq1, const shared_ptr<LinearEquation>& eq2) {
	return eq1->getSecondCoefficient() < eq2->getSecondCoefficient();
}
int main() {
	vector<shared_ptr<Equation>> equations;
	int a, b, c, option;
	cout << "chose '1' (Qwadric Equation) or '2' (Linear Equation) or '3' (stop enter) : ";
	cin >> option;
	while (option != 3) {
		if (option == 1) {
			cout << "enter 'a', 'b', 'c' : ";
			cin >> a >> b >> c;
			try {
				equations.push_back(make_shared<QwadricEquation>(a, b, c));
			}
			catch (const exception& e) {
				cerr << e.what() << endl;
			}
		}
		else if (option == 2) {
			cout << "enter 'a', 'b' : ";
			cin >> a >> b;
			equations.push_back(make_shared<LinearEquation>(a, b));
		}
		cout << "chose '1' (Qwadric Equation) or '2' (Linear Equation) or '3' (stop enter) : ";
		cin >> option;
	}
	ofstream out("DATA.txt");
	if (!out.is_open()) {
		cerr << "error with opening out file" << endl;
		return 1;
	}
	bool isPrint = false;
	for (const auto& eq : equations) {
		eq->print(out);
		eq->solve(out);
		out << endl;
		isPrint = true;
	}
	if (isPrint) cout << endl << "information was succesfully wrote in DATA.txt" << endl;
	else cout << endl << "there is no information to write down" << endl;
	out.close();
	isPrint = false;
	cout << endl << "equations that have no solutions" << endl;
	for (const auto& eq : equations) {
		if (!eq->hasSolution()) {
			eq->print(cout);
			isPrint = true;
		}
	}
	if (!isPrint) cout << "there is no such equations" << endl;
	cout << endl << "equations that have infinite number of solutions: ";
	int infCount = 0;
	for (const auto& eq : equations) {
		if (eq->hasInfiniteSolutions()) infCount++;
	}
	cout << infCount << endl;
	cout << endl << "sorted massiv" << endl;
	sort(equations.begin(), equations.end(), CompareCoefficients);
	for (const auto& eq : equations) {
		eq->print(cout);
	}
	cout << endl << "qwadric equations that have determinant < 0" << endl;
	isPrint = false;
	for (const auto& eq : equations) {
		auto quadEq = dynamic_pointer_cast<QwadricEquation>(eq);
		if (quadEq && quadEq->Determinant()) {
			quadEq->print(cout);
			isPrint = true;
		}
	}
	if (!isPrint) cout << "there is no such equations" << endl;
	cout << endl << "qwadric equations that have branches down" << endl;
	for (const auto& eq : equations) {
		auto quadEq = dynamic_pointer_cast<QwadricEquation>(eq);
		if (quadEq && quadEq->getLeadingCoefficient() < 0) {
			quadEq->print(cout);
		}
	}
	cout << endl << "qwadric equations that have square" << endl;
	isPrint = false;
	for (const auto& eq : equations) {
		auto quadEq = dynamic_pointer_cast<QwadricEquation>(eq);
		if (quadEq && quadEq->isSquare()) {
			quadEq->print(cout);
			isPrint = true;
		}
	}
	if (!isPrint) cout << "there is no such equations" << endl;
	cout << endl << "linear equations that have a < b and sorted by b" << endl;
	isPrint = false;
	vector < shared_ptr<LinearEquation>> lineEquations;
	for (const auto& eq : equations) {
		auto lineEq = dynamic_pointer_cast<LinearEquation>(eq);
		if (lineEq && (lineEq->getLeadingCoefficient() < lineEq->getSecondCoefficient())) {
			lineEquations.push_back(lineEq);
			isPrint = true;
		}
	}
	if (!isPrint) cout << "there is no such equations" << endl;
	sort(lineEquations.begin(), lineEquations.end(), CompareCoefficientAB);
	for (const auto& eq : lineEquations) {
		eq->print(cout);
	}
	return 0;
}