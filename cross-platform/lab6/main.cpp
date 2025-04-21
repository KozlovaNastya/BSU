#include "factory.h"
int main() {
	//counstructor
	Equation* p1 = Equation::CreateEquation(LinearEquationID, 2, 6, 3);
	p1->print(cout);
	Equation* p2 = Equation::CreateEquation(QwadricEquationID, 0, 4, 2);
	p2->print(cout);
	//class
	LinearEquationFactory* lef = new LinearEquationFactory;
	QwadricEquationFactory* qef = new QwadricEquationFactory;
	Equation* p3 = lef->CreateEquation(2, 3, 5);
	p3->print(cout);
	Equation* p4 = qef->CreateEquation(1, 0, 6);
	p4->print(cout);
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	return 0;
}
