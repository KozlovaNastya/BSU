#include "footballers.h"
#include <vector>
void CompressArray(std::vector<std::unique_ptr<Footballer>>& footballers, int minGames) {
int removedCount = 0;
for (auto& ftbl : footballers) {
	FootballerResult* resultPtr = dynamic_cast<FootballerResult*>(ftbl.get());
	if (resultPtr && resultPtr->getRealGames() < minGames) {
		ftbl.reset();
		removedCount++;
	}
}
std::cout << "Compressed Array:" << std::endl;
for (const auto& ftbl : footballers) {
	if (ftbl) std::cout << *ftbl;
	else std::cout << "nullptr (removed)" << std::endl;
}
if (removedCount > 0) std::cout << "Removed objects count: " << removedCount << std::endl;
else std::cout << "no removed objects" << std::endl;
}

int main() {
	std::cout << "FOOTBALLER" << std::endl;
	Footballer ft1("Less", Position::defender, 2026);
	Footballer ft2("Johan", Position::goalkeeper, 2030);
	std::cout << "constructor with parameteres" << std::endl;
	std::cout << ft1 << ft2;
	Footballer ft3(std::move(ft1));
	Footballer ft4 = std::move(ft2);
	std::cout << "copy constructor" << std::endl;
	std::cout << ft3;
	std::cout << "operator =" << std::endl;
	std::cout << ft4;
	std::cout << "FOOTBALLER RESULT" << std::endl;
	int ar1[12] = { 0,1,2,3,2,0,1,2,0,1,2,0 };
	int ar2[30] = { 0,1,2,3,2,0,1,2,0,1,2,0,5,10,2,0,2,3,0,15,0,2,0,2,2,1,2,2,0,1 };
	FootballerResult ft5("Yorich", Position::defender, 2022, 30, 12, ar1);
	FootballerResult ft6("Messi", Position::striker, 2000, 120, 12, ar1);
	std::cout << "constructor with parameteres" << std::endl;
	std::cout << ft5 << ft6;
	FootballerResult ft7(std::move(ft5));
	FootballerResult ft8 = std::move(ft6);
	std::cout << "copy constructor" << std::endl;
	std::cout << ft7;
	std::cout << "operator =" << std::endl;
	std::cout << ft8;
	std::cout << "operator ==" << std::endl;
	std::cout << "Footballer ft3 == Footballer ft4 : " << (ft3 == ft4) << std::endl;
	std::cout << "Footballer ft3 == FootballerResult ft7 : " << (ft3 == ft7) << std::endl;
	std::cout << "Footballer ft3 == FootballerResult ft8 : " << (ft3 == ft8) << std::endl;
	std::cout << "FootballerResult ft7 == FootballerResult ft8 : " << (ft7 == ft8) << std::endl;
	std::vector<std::unique_ptr<Footballer>> footballeres;
	footballeres.push_back(std::make_unique<Footballer>(std::move(ft3)));
	footballeres.push_back(std::make_unique<FootballerResult>(std::move(ft7)));
	footballeres.push_back(std::make_unique<Footballer>(std::move(ft4)));
	footballeres.push_back(std::make_unique<FootballerResult>(std::move(ft8)));
	footballeres.push_back(std::make_unique<FootballerResult>("Ronaldo", Position::goalkeeper, 2020, 140, 30, ar2));
	std::cout << "ARRAY OF FOOTBALLERS" << std::endl;
	for (const auto& ftbl : footballeres)
		std::cout << *ftbl;
	int countG = 0, countD = 0, countM = 0, countS = 0;
	for (const auto& ftbl : footballeres) {
		switch (ftbl->getPosition())
		{
		case Position::goalkeeper:
			countG++;
			break;
		case Position::defender:
			countD++;
			break;
		case Position::midfielder:
			countM++;
			break;
		case Position::striker:
			countS++;
			break;
		default:
			break;
		}
	}
	std::cout << "Number of goalkeepers: " << countG << std::endl;
	std::cout << "Number of defenderes: " << countD << std::endl;
	std::cout << "Number of midfielderes: " << countM << std::endl;
	std::cout << "Number of strikers: " << countS << std::endl;
	int countF = 0, countFR = 0;
	for (const auto& ftbl : footballeres) {
		auto ftblFR = dynamic_cast<FootballerResult*>(ftbl.get());
		if (ftblFR) countFR++;
		else countF++;
	}
	std::cout << "Number of Footboller: " << countF << std::endl;
	std::cout << "Number of FootbollerResult: " << countFR << std::endl;
	std::cout << "Year of footbollers is 2020" << std::endl;
	int year1 = 2020;
	bool isPrint1 = false;
	for (const auto& ftbl : footballeres) {
		if (ftbl->getYear() == year1) {
			std::cout << *ftbl;
			isPrint1 = true;
		}
	}
	if (!isPrint1) std::cout << "There is no such footbollers" << std::endl;
	std::cout << "Year of footbollers is 1990" << std::endl;
	int year2 = 1990;
	bool isPrint2 = false;
	for (const auto& ftbl : footballeres) {
		if (ftbl->getYear() == year2) {
			std::cout << *ftbl;
			isPrint2 = true;
		}
	}
	if (!isPrint2) std::cout << "There is no such footbollers" << std::endl;
	CompressArray(footballeres, 13);
	return 0;
}