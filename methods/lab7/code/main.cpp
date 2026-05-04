#include <iostream>
#include <iomanip>
#include "functions.h"

using namespace std;

void calculateMethod(const char* name, double (*method)(double, double, int), double a, double b, double eps, int p, double exact) {
    int n = 2;
    double i_n, i_2n;

    do {
        i_n = method(a, b, n);
        n *= 2;
        i_2n = method(a, b, n);
    } while (abs(i_2n - i_n) / (pow(2, p) - 1) > eps);

    double runge_error = (i_2n - i_n) / (pow(2, p) - 1);
    double corrected = i_2n + runge_error;

    cout << "--- " << name << " ---" << endl;
    cout << "Приближенное значение: " << i_2n << endl;
    cout << "Уточненное значение:   " << corrected << endl;
    cout << "Величина шага (h):     " << (b - a) / n << endl;
    cout << "Разность с точным:     " << abs(exact - i_2n) << endl << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a = 1.0, b = 4.0, eps = 1e-7;
    double exact = exp(1.0) - exp(0.25);

    cout << fixed << setprecision(10);
    cout << "Точное значение:       " << exact << endl << endl;

    calculateMethod("Метод левых прямоугольников", leftRect, a, b, eps, 1, exact);
    calculateMethod("Метод Симпсона", simpson, a, b, eps, 4, exact);

    double eps2 = 1e-4;
    int n2 = 2;
    double res1, res2;
    do {
        res1 = gaussChebyshev(n2);
        n2 *= 2;
        res2 = gaussChebyshev(n2);
    } while (abs(res2 - res1) > eps2);

    cout << "--- Задание 2 (Гаусс-Чебышев) ---" << endl;
    cout << "Результат: " << res2 << endl;
    cout << "Количество узлов: " << n2 << endl;


    return 0;
}
