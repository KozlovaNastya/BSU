#include "functions.h"

double f1(double x) {
    return (1.0 / (x * x)) * exp(1.0 / x);
}

double f2(double t) {
    return sin(4.0 * t + 6.0);
}

double gaussChebyshev(int n) {
    const double PI = acos(-1.0);
    double sum = 0;
    for (int i = 1; i <= n; ++i) {
        double t_i = cos((2.0 * i - 1.0) / (2.0 * n) * PI);
        sum += f2(t_i);
    }
    return (PI / n) * sum;
}


double leftRect(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;
    for (int i = 0; i < n; ++i) sum += f1(a + i * h);
    return sum * h;
}

double simpson(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f1(a) + f1(b);
    for (int i = 1; i < n; i += 2) sum += 4 * f1(a + i * h);
    for (int i = 2; i < n - 1; i += 2) sum += 2 * f1(a + i * h);
    return sum * h / 3.0;
}