#include "footballers.h"
int countID = 0;
std::string PositionToString(Position pos) {
	switch (pos)
	{
	case Position::goalkeeper:
		return "goalkeeper";
	case Position::defender:
		return "defender";
	case Position::midfielder:
		return "midfielder";
	case Position::striker:
		return "striker";
	default:
		return "unknown";
	}
}
Footballer::Footballer(const std::string& surname, Position position, int year)
	:ID(countID++), surname(surname), position(position), year(year) {}
Footballer::Footballer(Footballer&& other)
: ID(countID++), surname(std::move(other.surname)), position(other.position), year(other.year){} 
Footballer& Footballer::operator=(Footballer&& other) {
	if (this != &other) {
		surname = std::move(other.surname);
		position = other.position;
		other.surname = ""; //так как передали владение 'чистим' игрока
	}
	return *this;
}
bool Footballer::operator==(const Footballer& other) {
	if (position == other.position) return true;
	return false;
}
void Footballer::setSurname(const std::string& sur) {
	surname = sur;
}
void Footballer::setPosition(Position pos) {
	position = pos;
}
int Footballer::getID() const { return ID; }
std::string Footballer::Footballer::getSurname() const { return surname; }
Position Footballer::getPosition() const { return position; }
int Footballer::getYear() const { return year; }
std::ostream& operator<<(std::ostream& os, const Footballer& other) {
	os << other.ID << ';' << other.surname << ';' << PositionToString(other.position) << ';' << other.year << std::endl;
	return os;
}
FootballerResult::FootballerResult(const std::string& surname, Position pos, int year, int maxGames, int realGames, const int* gls)
	: Footballer(surname, pos, year), maxGames(maxGames), realGames(realGames) {
	goals = new int[realGames];
	for (int i = 0; i < realGames; i++)
		goals[i] = gls[i];
}
FootballerResult::FootballerResult(FootballerResult&& other)
: Footballer(std::move(other)), maxGames(other.maxGames), realGames(other.realGames), goals(other.goals){
	other.goals = nullptr;
	other.realGames = 0;
}
FootballerResult& FootballerResult::operator = (FootballerResult&& other) {
	if (this != &other) {
		Footballer::operator=(std::move(other));
		realGames = other.realGames;
		delete[]goals;
		goals = other.goals;
		other.goals = nullptr;
		other.realGames = 0;
	}
	return *this;
}
void FootballerResult::setRealGames(int games) { realGames = games; }
void FootballerResult::setGoals(const int* gls) {
	delete[] goals;
	goals = new int[realGames];
	for (int i = 0; i < realGames; i++)
		goals[i] = gls[i];
}
int FootballerResult::getMaxGames() const { return maxGames; }
int FootballerResult::getRealGames() const { 
	if (realGames > maxGames)
		throw std::out_of_range("realGames cannot be grater than maxGames!");
	return realGames; 
}
int* FootballerResult::getGoals() const { return goals; }
std::ostream& operator<<(std::ostream& os, const FootballerResult& other) {
	os << other.getID() << ';' << other.getSurname()<< ';' << PositionToString(other.getPosition()) << ';' << other.getYear() <<
		';' << other.maxGames << ';' << other.realGames << std::endl << "list of goals" << std::endl;
	for (int i = 0; i < other.realGames; i++) {
		os << other.goals[i];
		if (i != other.realGames - 1) os << ';';
	}
	os << std::endl;
	return os;
}
FootballerResult::~FootballerResult() {
	delete[] goals;
}