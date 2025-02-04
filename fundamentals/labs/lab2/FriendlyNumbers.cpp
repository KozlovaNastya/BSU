#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int N;
	int s1, s2, a, b;
	int count = 0;
	cout << "Enter a limit" << endl;
	cin >> N;
	for (int i = 1; i < N; i++) {
		s1 = 0;
		for (a = 1; a < i-1; a++) {
			if (i % a == 0)
				s1 = s1 + a;
		}
		s2 = 0;
		for (b = 1; b < s1-1; b++) {
			if (s1 % b == 0)
				s2 = s2 + b;
		}
		if (s1 > i && s2 == i && s1 != i) {
			cout << "Numbers " << s2 << " and " << s1 << " are friendly" << endl;
			count++;
		}
	}
	if(count == 0)
		cout << "There are no friendly numbers in the given range" << endl;
	return 0;
}
