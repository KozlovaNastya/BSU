#include <iostream>
#include <ctime>
#include <cctype>
#include <string>
#include <vector>
using namespace std;
int getValue1(const int nmax) {
	while (true) {

		int n;
		string n1;
		vector <int> n2;
		getline(cin, n1);
		for (int i = 0; i < n1.length(); i++) {
			if (isspace(n1[i]))
			{
				break;
			}
			else if (isalpha(n1[i])) {
				break;
			}
			else n2[i] += n1[i];
			cout << n2[i];
		}
		
		if (cin.fail() || n >= nmax || n <= 1) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid entry, please try again" << endl;
		}
		else
		{
			std::cin.ignore(32767, '\n');
			return n;
		}
	}
}
int getValue2() {
	while (true) {
		int otv;
		cout << "Do you want to fill the array yourself? (answers: yes = 1; no = 0)" << endl;
		cin >> otv;
		if (cin.fail() || otv != 1 && otv != 0) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid entry, please try again" << endl;
		}
		else
		{
			std::cin.ignore(32767, '\n');
			return otv;
		}
	}
}
int getValue3() {
	while (true) {
		int ch;
		cin >> ch;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid entry, please try again" << endl;
		}
		else
		{
			std::cin.ignore(32767, '\n');
			return ch;
		}
	}
}
int znak(int array[], int n) {
	int kol = 0;
	for (int i = 0; i < n-1; i++)
		if (array[i] >= 0 && array[i + 1] < 0 || array[i] < 0 && array[i + 1] >= 0)
			kol++;
	return kol;
}
void proiz(int array[], int n) {
	int proiz, kol1, kol2, i;
	proiz = 1;
	kol1 = 0;
	kol2 = 0;
	for (i = 0; i < n; i++)
		if (array[i] == 0) {
			kol1 = i;
			break;
		}
	for (i = kol1+1; i < n; i++)
		if (array[i] == 0) {
			kol2 = i;
			break;
		}
	if (kol2 == 0)
		cout << "There are no two zero elements" << endl;
	else {
		for (i = kol1 + 1; i < kol2; i++)
			proiz *= array[i];
		cout << "Product of array elements located between the first and second zero elements =" << proiz << endl;
	}
}
void uborka(int array[], int n, int P) {
	int chet = 0;
	for (int i = 0; i < n; i++)
		if (array[i] == P)
			chet++;
	if (chet == 0)
		cout << "There are no such elements in the array";
	else {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n - 1 - i; j++)
				if (array[j] == P) {
					array[j] = array[j + 1];
					array[j + 1] = P;
				}
	for (int i = 0; i < n; i++)
		if (array[i] == P)
			array[i] = 0;
	cout << "New array:" << endl;
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	}
}
int main() {
	setlocale(LC_ALL, ".1251");
	const int nmax = 10;
	int P, array[nmax];
	cout << "Enter size 1 <= number of array elements >=" << nmax << endl;
	int n = getValue1(nmax);
	int otv = getValue2();
	cout << "Enter the lower limit of the interval" << endl;
	int niz = getValue3();
	cout << "Enter the upper limit of the interval" << endl;
	int verh = getValue3();
	if (otv == 1) {
		cout << "Enter Array Elements:" << endl;
		for (int i = 0; i < n; i++)
			cin >> array[i];
	}
	else {
		srand(time(0));
		for (int i = 0; i < n; i++) 
			array[i] = niz + rand() % verh;
	}
	cout << "Source array:" << endl;
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl << "Number of sign changes = " << znak(array, n) << endl;
	proiz(array, n);
	cout << "Enter the element you want to remove" << endl;
	cin >> P;
	uborka(array, n, P);
	return 0;
}
