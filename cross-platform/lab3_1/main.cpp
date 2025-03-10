#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <set>
#include <locale>
using namespace std;
class Film {
private:
	string name;
	int year;
	vector<string> actors;
public:
	Film(string name, int year, vector<string> actors) :name(name), year(year), actors(actors) {}
	int getYear() const { return year; }
	string getName() const { return name; }
	vector<string> getActors() const { return actors; }
	vector<string>& getActorsRef() { return actors; }
	friend ostream& operator<< (ostream& out, const Film& data) {
		out << data.name << ";" << data.year << ";";
		for (int i = 0; i < data.actors.size(); i++) {
			out << data.actors[i];
			if (i < data.actors.size() - 1)
				out << ',';
		}
		out << endl;
		return out;
	}
};
bool compareNames(const Film& a, const Film& b) {
	return a.getName() < b.getName();
}
bool compareYear(const Film& a, const Film& b) {
	if (a.getYear() == b.getYear())
		return compareNames(a, b);
	return a.getYear() < b.getYear();
}
bool findActor(const Film& a, const string& word) {
	vector<string> v = a.getActors();
	auto it = find(v.begin(), v.end(), word);
	if (it != v.end()) return true;
	else return false;
}
string& toLowerCase(string& word) {
	for (char& a : word) {
		if ((unsigned char)a >= 192 && (unsigned char)a <= 223)
			a += 32;
		else a = tolower((unsigned char)a);
	}
	return word;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream input("DATA.txt");
	if (!input.is_open()) {
		cerr << "input file is not open" << endl;
		return 1;
	}
	if (input.peek() == EOF) {
		cerr << "input file is empty" << endl;
		return 1;
	}
	vector<Film> listOfFilms;
	string line;
	while (getline(input, line)) {
		int pos1 = line.find(';');
		if (pos1 == string::npos) continue;
		string name = line.substr(0, pos1);
		toLowerCase(name);
		int pos2 = line.find(';', pos1 + 1);
		if (pos2 == string::npos) continue;
		int year = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
		int start = pos2 + 1;
		int pos = line.find(',', start);
		vector<string> actors;
		while (pos != string::npos) {
			actors.push_back(line.substr(start, pos - start));
			start = pos + 1;
			pos = line.find(',', start);
		}
		actors.push_back(line.substr(start));
		if (actors.empty() || actors[0] == "") continue;
		for (string& actor : actors)
			toLowerCase(actor);
		Film film(name, year, actors);
		listOfFilms.push_back(film);
	}
	input.close();
	if (listOfFilms.empty()) {
		cout << "list is empty" << endl;
		return 1;
	}
	cout << "sorted massive" << endl;
	sort(listOfFilms.begin(), listOfFilms.end(), compareYear);
	for (const auto& film : listOfFilms)
		cout << film;
	cout << "all actors" << endl;
	set<string> allActors;
	for (const auto& film : listOfFilms) {
		for (const auto& actor : film.getActors())
			allActors.insert(actor);
	}
	if (allActors.empty())
		cout << "list of actors is empty" << endl;
	else {
		for (const auto& actor : allActors)
			cout << actor << endl;
	}
	cout << "find count of films without 'helena'" << endl;
	int count = 0;
	string word = "helena";
	for (const auto& film : listOfFilms) {
		if (!findActor(film, word))
			count++;
	}
	cout << count << endl;
	cout << "find films with 'helena'" << endl;
	bool isOut = false;
	for (const auto& film : listOfFilms) {
		if (findActor(film, word)) {
			cout << film.getName() << endl;
			isOut = true;
		}
	}
	if (!isOut)
		cout << "there is no such films" << endl;
	cout << "replace 'helena' with 'andrey'" << endl;
	string word1 = "andrey";
	for (auto& film : listOfFilms) {
		if (findActor(film, word)) {
			vector<string>& v = film.getActorsRef();
			auto it = find(v.begin(), v.end(), word);
			if (it != v.end()) {
				*it = word1;
				cout << *it;
			}
		}
	}
	for (const auto& film : listOfFilms)
		cout << film;
	return 0;
}
