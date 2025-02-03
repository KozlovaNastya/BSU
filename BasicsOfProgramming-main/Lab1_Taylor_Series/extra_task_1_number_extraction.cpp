#include <iostream> 
#include <cstdlib> 
#include <string>
#include <cstring> 
using namespace std;
int main() {
	string str = " 34 BGU 67U -9e + 678e+2;;; -5; 1 + 2;; 123E-2 - k345; :-1s1 77e + 22";
	string d = " ,;:", w;
	size_t pos1 = 0, pos2, pos;
	bool is_number;
	str = str + d;
	while ((pos1 = str.find_first_not_of(d, pos1)) != -1) {
		is_number = false;
		pos2 = str.find_first_of(d, pos1);
		w = str.substr(pos1, pos2 - pos1);
		if (w[0] == '+' || w[0] == '-') {
			if (w[1] >= '0' && w[1] <= '9') 
				is_number = true;
		}
		else {
			if (w[0] >= '0' && w[0] <= '9') 
				is_number = true;
		}
		if (!is_number) {
			pos1 = pos2;
		}
		else {
			stod(w, &pos);
			if ((w.length() == pos || w.length() == pos + 1 
				&& (w[pos] == 'l' || w[pos] == 'L' 
				|| w[pos] == 'u' || w[pos] == 'U' 
				|| w[pos] == 'f' || w[pos] == 'F')))
				cout << w << endl;
			pos1 = pos2;
		}
	}
	return 0;
}