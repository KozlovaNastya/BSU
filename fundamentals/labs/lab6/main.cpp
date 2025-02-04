#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//функци€ дл€ проверки на строговозрастающую подстроку
bool Proverka(const string& subline) { 
	for (int i = 1; i < subline.length(); i++) {
		if (subline[i - 1] >= subline[i]) // ≈сли текущий символ не больше предыдущего
			return false; // ¬озвращаем false, если не строго возрастающа€
	}
	return true; // ¬озвращаем true, если слово строго возрастающее
}
//функци€ нахождени€ максимальной строго возрастающей подстроки
string MaxsubLine(const string& line) { 
	string subline; //переменна€ дл€ подстроки
	string maxsubline; //переменна€ дл€ максимальной подстроки
	int pos = 0; //переменна€ дл€ позиции начала подстроки
	while (pos < line.length()) { //разбиваем на подстроки
		size_t space = line.find(' ', pos); //позици€ пробела
		if (space == string::npos)
			space = line.length(); // ≈сли пробелов больше нет, берем до конца строки
		subline = line.substr(pos, space - pos); //копируем подстроку
		pos = space + 1; //переходим к следующему слову
		if (Proverka(subline) && maxsubline.length() < subline.length()) //проверка на строгое возрастание и максимальную подстроку
				maxsubline = subline;
		}
	return maxsubline;
}
int main() {
	setlocale(LC_ALL, ".1251");
	ifstream in("input.txt"); //открываем файл дл€ чтени€
	if (!in.is_open()) {
		cerr << "ERROR with input.txt"; //выполн€ем проверку на открытие файла
		return 1;
	}
	string line; //переменна€ дл€ строки из файла
	int count = 0; //счетчик дл€ выведеных строк
	while (getline(in, line) && count < 10) { //читаем строки пока в файле есть информаци€ и пока не выведем 10 строк
		string subline = MaxsubLine(line);
		if (!subline.empty())
			cout << ++count << ". ћаксимальна€ строговозрастающа€ подстрока: " << subline << endl << "¬ строке: " << line << endl << endl;
	}
	in.close(); //закрываем файл
	return 0;
}