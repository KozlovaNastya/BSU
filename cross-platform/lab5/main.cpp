#include "character.h"
#include <vector>
#include <algorithm>
bool AlphaSort(const std::unique_ptr<Character>& ch1, const std::unique_ptr<Character>& ch2) {
	return ch1->getName() < ch2->getName();
}
int main() {
	Character ch1("Legolas", Condition::normal, Race::elf, 15, 5);
	cout << "constructor with parameters" << endl << ch1;
	Character ch2(std::move(ch1));
	cout << "copy constructor" << endl << ch2;
	Character ch3 = std::move(ch2);
	cout << "operator =" << endl << ch3;
	cout << "for ch1" << endl <<
		"getID() : " << ch1.getID() << endl <<
		"getName() : " << ch1.getName() << endl <<
		"getCondition() : " << ConditionToString(ch1.getCondition()) << endl <<
		"getRace() : " << RaceToString(ch1.getRace()) << endl <<
		"getSpeed() : " << ch1.getSpeed() << endl <<
		"getArtifacts() : " << ch1.getArtifacts() << endl;
	cout << "setName(), setCondition(), setSpeed(), setArtifacts() for ch2" << endl;
	ch2.setName("Lucy");
	ch2.setCondition(Condition::paralyzed);
	ch2.setSpeed(0);
	ch2.setArtifacts(1);
	cout << ch2;
	cout << "compare by ID" << endl <<
		"ch1 < ch2 : " << (ch1 < ch2) << endl <<
		"ch3 < ch1 : " << (ch3 < ch1) << endl;
	cout << "MAGIC CHARACTERS" << endl;
	Artefacts art1[] = { Artefacts::amulet, Artefacts::potion };
	MagicCharacter ch4("Elvin", Condition::normal, Race::human, 20, 5, 50, 37, 2, art1);
	cout << "constructor with parameters" << endl << ch4;
	MagicCharacter ch5(std::move(ch4));
	cout << "copy constructor" << endl << ch5;
	MagicCharacter ch6 = std::move(ch4);
	cout << "operator =" << endl << ch6;
	cout << "for ch4:" << endl <<
		"getID() : " << ch4.getID() << endl <<
		"getName() : " << ch4.getName() << endl <<
		"getCondition() : " << ConditionToString(ch4.getCondition()) << endl <<
		"getRace() : " << RaceToString(ch4.getRace()) << endl <<
		"getSpeed() : " << ch4.getSpeed() << endl <<
		"getArtifacts() : " << ch4.getArtifacts() << endl <<
		"getMaxMana() : " << ch4.getMaxMana() << endl <<
		"getMana() : " << ch4.getMana() << endl << 
	    "getMagicArtefacts() : " << ch4.getMagicArtefacts() << endl;
	const int n = ch4.getMagicArtefacts();
	Artefacts* list = ch4.getListOfArtefacts();
	cout << "List of Magic Artefacts: ";
	for (int i = 0; i < n; i++)
		cout << ArtefactsToString(list[i]) << " ";
	cout << "setName(), setCondition(), setSpeed(), setArtifacts() for ch5" << endl;
	Artefacts art2[1];
	ch5.setName("Anna");
	ch5.setCondition(Condition::dead);
	ch5.setSpeed(0);
	ch5.setArtifacts(0);
	ch5.setMaxMana(90);
	ch5.setMana(0);
	ch5.setMagicArtefacts(0);
	ch5.setListOfArtefacts(art2);
	cout << ch5;
	cout << "compare by ID" << endl <<
		"ch4 < ch5 : " << (ch4 < ch5) << endl <<
		"ch6 < ch5 : " << (ch6 < ch5) << endl;
	cout << "array with two types of characters" << endl;
	std::vector<std::unique_ptr<Character>> ar;
	ar.push_back(std::make_unique<Character>("Legolas", Condition::normal, Race::elf, 15, 5));
	ar.push_back(std::make_unique<Character>("Lucy", Condition::paralyzed, Race::human, 10, 3));
	ar.push_back(std::make_unique<MagicCharacter>("Elvin", Condition::normal, Race::human, 20, 5, 50, 37, 2, art1));
	std::sort(ar.begin(), ar.end(), AlphaSort);
	for (const auto& ch : ar) {
		cout << *ch;
	}
	int countCh = 0, countM = 0;
	for (const auto& ch : ar) {
		auto chM = dynamic_cast<MagicCharacter*>(ch.get());
		if (chM) countM++;
		else countCh++;
	}
	cout << "Number of Character: " << countCh << endl;
	cout << "Number of MagicCharacter: " << countM << endl;
	return 0;
}