#pragma once
#include <string>
#include <iostream>
extern int countID;
enum class Position { goalkeeper, defender, midfielder, striker };
class Footballer {
private:
	const int ID;
	std::string surname;
	Position position;
	const int year;
public:
	Footballer() = delete;
	Footballer(const std::string& surname, Position position, int year);
	Footballer(Footballer&& other);
	Footballer(const Footballer&) = delete;
	Footballer& operator=(const Footballer& other ) = delete;
	Footballer& operator=(Footballer&& other);
	bool operator==(const Footballer& other);
	void setSurname(const std::string& sur);
	void setPosition(Position pos);
	int getID() const;
	std::string getSurname() const;
	Position getPosition() const;
	int getYear() const;
	friend std::ostream& operator<<(std::ostream& os, const Footballer& other);
	virtual ~Footballer() = default;
};
class FootballerResult : public Footballer{
private:
	const int maxGames;
	int realGames;
	int* goals;
public:
	FootballerResult() = delete;
	FootballerResult(const std::string& surname, Position position, int year, int maxGames, int realGames, const int* goals);
	FootballerResult(FootballerResult&& other);
	FootballerResult& operator = (FootballerResult&& other);
	void setRealGames(int games);
	void setGoals(const int* gls);
	int getMaxGames() const;
	int getRealGames() const;
	int* getGoals() const;
	friend std::ostream& operator<<(std::ostream& os, const FootballerResult& other);
	~FootballerResult();
};