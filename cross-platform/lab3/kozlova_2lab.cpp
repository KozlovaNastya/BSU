//Козлова Анастасия, 10 группа
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <set>
#include <locale>
using namespace std;
class Flowers {
private:
	int num;
	string shape;
	vector<string> flow;
public:
	Flowers(int num, string shape, vector<string> flow) : num(num), shape(shape), flow(flow){}
	int getNum() const { return num; }
	string getShape() const { return shape; }
	vector<string> getFlow() const{ return flow; }
	vector<string>& getFlowRef() { return flow; } 
	friend ostream& operator<<(ostream& out, const Flowers& other) {
		out << other.num << ';' << other.shape << ';';
		for (size_t i = 0; i < other.flow.size(); ++i) {
			out << other.flow[i];
			if (i < other.flow.size() - 1) out << ',';
		}
		out << endl;
		return out;
	}
};
bool cmpNum(const Flowers& a, const Flowers& b) {
	return a.getNum() < b.getNum();
}
bool cmpShape(const Flowers& a, const Flowers& b) {
	if (a.getShape() == b.getShape())
		return cmpNum(a, b);
	return a.getShape() > b.getShape();
}
bool findFlow(const Flowers& a, const string& word) {
	vector<string> f = a.getFlow();
	auto it = find(f.begin(), f.end(), word);
	if (it != f.end()) {
		return true;
	}
	else {
		return false;
	}
}
string& toLowerCase(string& word) {
	for (char& a : word) {
		if ((unsigned char)a >= 192 && (unsigned char)a <= 223) {
			a += 32;
		}
		else {
			a = tolower((unsigned char)a);
		}
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
	string line;
	vector<Flowers> flowersS;
	while (getline(input, line)) {
		int pos1 = line.find(';');
		if (pos1 == string::npos) continue;
		int num = stoi(line.substr(0, pos1));
		int pos2 = line.find(';', pos1 + 1);
		if (pos2 == string::npos) continue;
		string shape = line.substr(pos1 + 1, pos2 - pos1 - 1);
		toLowerCase(shape);
		vector<string> flow;
		int start = pos2 + 1;
		int pos = line.find(',', start);
		while (pos != string::npos) {
			flow.push_back(line.substr(start, pos - start));
			start = pos + 1;
			pos = line.find(',', start);
		}
		flow.push_back(line.substr(start));
		for (string& f : flow) {
			toLowerCase(f);
		}
		Flowers f(num, shape, flow);
		flowersS.push_back(f);
	}
	input.close();
	cout << "отсортированно по формам" << endl;
	sort(flowersS.begin(), flowersS.end(), cmpShape);
	if (!flowersS.empty()) {
		for (auto f : flowersS)
			cout << f;
	}
	cout << "список всех цветов" << endl;
	set<string> listOfFlow;
	for (auto flowers : flowersS) {
		for (auto f : flowers.getFlow()) {
			listOfFlow.insert(f);
		}
	}
	if (listOfFlow.empty()) {
		cout << "Список всех цветов пуст!" << endl;
	}
	else {
		for (auto f : listOfFlow) {
			cout << f << endl;
		}
	}
	cout << "номера клумб на которых нет 'ромашка'" << endl;
	string word = "ромашка";
	for (auto flowers : flowersS) {
		if (!findFlow(flowers, word)) {
			cout << flowers.getNum() << endl;
		}
	}
	cout << "общие цветы для всех клумб" << endl;
	if (flowersS.empty()) {
		cout << "Нет данных о клумбах!" << endl;
		return 1;
	}
	vector<string> allFlowers = flowersS[0].getFlow();
	set<string> f1(allFlowers.begin(), allFlowers.end());
	set<string> f3;
	for (const auto& flower : f1) {
		bool isFind = true;
		for (size_t i = 1; i < flowersS.size(); i++) {
			vector<string> allFlowers2 = flowersS[i].getFlow();
			set<string> f2(allFlowers2.begin(), allFlowers2.end());
			if (f2.find(flower) == f2.end()) {
				isFind = false;
				break;
			}
		}
		if (isFind) {
			f3.insert(flower);
		}
	}
	if (!f3.empty()) {
		for (auto f : f3) {
			cout << f << endl;
		}
	}
	else {
		cout << "Нет цветов, которые растут на всех клумбах!" << endl;
	}
	cout << "количество клумб на которых растет 2 вида цветков" << endl;
	int count = 0;
	for (auto f : flowersS) {
		if (f.getFlow().size() == 2) {
			count++;
		}
	}
	cout << count << endl;
	cout << "удалим со всех строк 'ромашка'" << endl;
	for (auto& f : flowersS) {
		auto& flow = f.getFlowRef();
		flow.erase(remove(flow.begin(), flow.end(), word), flow.end());
	}
	if (!flowersS.empty()) {
		for (auto f : flowersS)
			cout << f;
	}
	else {
		cout << "нет данных!" << endl;
	}
	return 0;
}