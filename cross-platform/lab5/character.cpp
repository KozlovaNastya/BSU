#include "character.h"
int countID = 0;
Character::Character(const string& name, Condition con, const Race race, int speed, int artifacts)
	: ID(countID++), name(name), condition(con), race(race), speed(speed), artifacts(artifacts) {}
Character::Character(Character&& other)
	: ID(countID++), name(std::move(other.name)), condition(other.condition), race(other.race), speed(other.speed), artifacts(other.artifacts) {
	other.condition = Condition::dead;
	other.speed = 0;
	other.artifacts = 0;
}
Character& Character::operator = (Character&& other) {
	if (this != &other) {
		name = std::move(other.name);
		condition = other.condition;
		speed = other.speed;
		artifacts = other.artifacts;
		other.condition = Condition::dead;
		other.speed = 0;
		other.artifacts = 0;
	}
	return *this;
}
const int Character::getID() const { return ID; }
string Character::getName() const { return name; }
Condition Character::getCondition() const { return condition; }
const Race Character::getRace() const { return race; }
int Character::getSpeed() const { return speed; }
int Character::getArtifacts() const { return artifacts; }
void Character::setName(string n){ name = n; }
void Character::setCondition(Condition con) { condition = con; }
void Character::setSpeed(int sp) { speed = sp; }
void Character::setArtifacts(int art) { artifacts = art; }
bool Character::operator < (const Character& other) const { return ID < other.ID; }
std::ostream& operator<<(std::ostream& os, const Character& other) {
	os << "ID: " << other.ID << "; Name: " << other.name << "; Condition: " << ConditionToString(other.condition)
		<< "; Race: " << RaceToString(other.race) << "; Speed: " << other.speed << "; Artifacts: " << other.artifacts << ';' << endl;
	return os;
}
string ConditionToString(Condition condition) {
	switch (condition)
	{
	case Condition::normal:
		return "normal";
	case Condition::paralyzed:
		return "paralyzed";
	case Condition::dead:
		return "dead";
	default:
		return "unknown";
	}
}
string RaceToString(Race race) {
	switch (race)
	{
	case Race::human:
		return "human";
	case Race::dwarf:
		return "dwarf";
	case Race::elf:
		return "elf";
	default:
		return "unknown";
	}
}
MagicCharacter::MagicCharacter(const string& name, Condition con, const Race race, int speed, int artifacts,
	unsigned int maxMana, unsigned int mana, int magicArtefacts, const Artefacts* list)
	: Character(name, con, race, speed, artifacts), maxMana(maxMana), mana(mana), magicArtefacts(magicArtefacts) {
	listOfArtefacts = new Artefacts[magicArtefacts];
	for (int i = 0; i < magicArtefacts; i++)
		listOfArtefacts[i] = list[i];
}
MagicCharacter::MagicCharacter(MagicCharacter&& other) : Character(std::move(other)), maxMana(other.maxMana), 
	mana(other.mana), magicArtefacts(other.magicArtefacts), listOfArtefacts(other.listOfArtefacts){
	other.listOfArtefacts = nullptr;
	other.magicArtefacts = 0;
}
MagicCharacter& MagicCharacter::operator = (MagicCharacter&& other) {
	if (this != &other) {
		Character::operator=(std::move(other));
		maxMana = other.maxMana;
		mana = other.mana;
		magicArtefacts = other.magicArtefacts;
		delete[]listOfArtefacts;
		listOfArtefacts = other.listOfArtefacts;
		other.listOfArtefacts = nullptr;
		other.magicArtefacts = 0;
	}
	return *this;
}
unsigned int MagicCharacter::getMaxMana() const {
	return maxMana;
}
unsigned int MagicCharacter::getMana() const { return mana; }
int MagicCharacter::getMagicArtefacts() const {	return magicArtefacts; }
Artefacts* MagicCharacter::getListOfArtefacts() const { return listOfArtefacts; }
void MagicCharacter::setMaxMana(unsigned int max) {	maxMana = max; }
void MagicCharacter::setMana(unsigned int mn) {	mana = mn; }
void MagicCharacter::setMagicArtefacts(int magicArt) { magicArtefacts = magicArt; }
void MagicCharacter::setListOfArtefacts(const Artefacts* list) {
	delete[] listOfArtefacts;
	listOfArtefacts = new Artefacts[magicArtefacts];
	for (int i = 0; i < magicArtefacts; i++)
		listOfArtefacts[i] = list[i];
}
std::ostream& operator << (std::ostream& os, const MagicCharacter& other) {
	os << "ID: " << other.getID() << "; Name: " << other.getName() << "; Condition: " << ConditionToString(other.getCondition())
		<< "; Race: " << RaceToString(other.getRace()) << "; Speed: " << other.getSpeed() << "; Artifacts: " << other.getArtifacts()
		<< "; Max Mana: " << other.maxMana << "; mana: " << other.mana << "; count of Magic Artefacts: " << other.magicArtefacts <<
		endl << "list of magic Artefacts:" << endl;
	for (int i = 0; i < other.magicArtefacts; i++)
		os << ArtefactsToString(other.listOfArtefacts[i]) << endl;
	return os;
}string ArtefactsToString(Artefacts art) {
	switch (art)
	{
	case Artefacts::sword:
		return "sword";
	case Artefacts::staff:
		return "staff";
	case Artefacts::rune:
		return "rune";
	case Artefacts::potion:
		return "potion";
	case Artefacts::amulet:
		return "amulet";
	default:
		return "unknown";
	}
}