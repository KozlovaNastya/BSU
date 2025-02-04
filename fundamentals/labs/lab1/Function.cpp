#include <cmath>
float Function(float e, float x) {
	int n;
	float sum, a;
	a = x;
	n = 1;
	sum = 0;
	while (abs(a) > e/10) {
		sum = sum + a;
		a = a * x * x * n/ (n + 2);
		n = n + 2;
	}
	return sum * 2;
}
float Log1(float x) {
	return log(((1 + x) / (1 - x)));
}