#include "composite.h"
int main() {

	Equation* eq1 = new LinearEquation(1, 2);
	Equation* eq2 = new QwadricEquation(2, 2, 5);
	CompositeEquation* equations = new CompositeEquation;
	equations->addEquation(eq1);
	equations->addEquation(eq2);
	equations->solve(cout);
	cout << equations->getLeadingCoefficient() << endl;
	delete equations;
	return 0;
}
