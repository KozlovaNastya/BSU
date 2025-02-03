#include <iostream>
#include <cmath>
using namespace std;
double C(double sum) {
	int b = 1;
	for (int i = 2; i < 6; i++) {
		sum = i * i + sum;
		sum = b*i*sqrt(sum);
		b = b * i;
	}
	return sum;
}
int main() {
	int x;
	cin >> x;
	cout << C((sqrt(1 + x))) << endl;
	cout << 2 * 3 * 4 * 5 * sqrt(5 * 5 + 2 * 3 * 4 * sqrt(4 * 4 + 2 * 3 * sqrt(3 * 3 + 2 * sqrt(2 * 2 + sqrt(1 + fabs(x))))));
	return 0;
}
