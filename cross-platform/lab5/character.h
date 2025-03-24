#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::endl;
enum class Condition { normal, paralyzed, dead };
enum class Race { human, dwarf, elf };
enum class Artefacts {sword, staff, rune, potion, amulet};
extern int countID;
class Character {
private:
	const int ID;
	string name;
	Condition condition;
	const Race race;
	int speed;
	int artifacts;
public:
	Character(const string& name, Condition con, const Race race, int speed, int artifacts);
	Character(Character&& other);
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;
	Character& operator = (Character&& other);
	const int getID() const;
	string getName() const;
	Condition getCondition() const;
	const Race getRace() const;
	int getSpeed() const;
	int getArtifacts() const;
	void setName(string n);
	void setCondition(Condition con);
	void setSpeed(int sp);
	void setArtifacts(int art);
	bool operator <(const Character& other) const;
	friend std::ostream& operator <<(std::ostream& os, const Character& other);
	virtual ~Character() = default;
};
string ConditionToString(Condition condition);
string RaceToString(Race race);
class MagicCharacter : public Character {
private:
	unsigned int maxMana;
	unsigned int mana;
	int magicArtefacts;
	Artefacts* listOfArtefacts;
public:
	MagicCharacter(const string& name, Condition con, const Race race, int speed, int artifacts,
		unsigned int maxMana, unsigned int mana, int magicArtefacts, const Artefacts* list);
	MagicCharacter(MagicCharacter&& other);
	MagicCharacter& operator = (MagicCharacter&& other);
	unsigned int getMaxMana() const;
	unsigned int getMana() const;
	int getMagicArtefacts() const;
	Artefacts* getListOfArtefacts() const;
	void setMaxMana(unsigned int max);
	void setMana(unsigned int mn);
	void setMagicArtefacts(int magicArt);
	void setListOfArtefacts(const Artefacts* list);
	friend std::ostream& operator << (std::ostream& os, const MagicCharacter& other);
	~MagicCharacter() {
		delete[] listOfArtefacts;
	}
};
string ArtefactsToString(Artefacts art);
#endif