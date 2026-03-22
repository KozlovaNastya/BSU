#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "interpolation.h"
#include "functions.h"

// Функция для вывода аналитического вида многочлена 2-й степени
void print_analytical_form(const std::string& label, const std::vector<double>& nodes, const std::vector<double>& coeffs) {
    std::cout << "  " << label << " P2(x) = "
        << coeffs[0] << " + ("
        << coeffs[1] << ")*(x - (" << nodes[0] << ")) + ("
        << coeffs[2] << ")*(x - (" << nodes[0] << "))*(x - (" << nodes[1] << "))\n";
}

void run_task(const std::string& func_name,
    std::function<double(double)> f,
    std::function<double(double)> f_double_prime,
    double a, double b) {

    std::vector<int> degrees = { 2, 4, 8, 16 };
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "ФУНКЦИЯ: " << func_name << " на отрезке [" << a << ", " << b << "]\n";

    for (int n : degrees) {
        // 1. Равномерная сетка (Задание 1)
        std::vector<double> nodes_reg(n + 1), y_reg(n + 1), coeffs_reg;
        generateNode(nodes_reg, a, b);
        for (int i = 0; i <= n; i++) y_reg[i] = f(nodes_reg[i]);
        calculateRazdRaznosti(nodes_reg, coeffs_reg, y_reg);

        // 2. Чебышевская сетка (Задание 2)
        std::vector<double> nodes_cheb(n + 1), y_cheb(n + 1), coeffs_cheb;
        generateChebishNodes(nodes_cheb, a, b);
        for (int i = 0; i <= n; i++) y_cheb[i] = f(nodes_cheb[i]);
        calculateRazdRaznosti(nodes_cheb, coeffs_cheb, y_cheb);

        // 3. Сплайны (Задание 3)
        auto splines = buildSpline(nodes_reg, y_reg, f_double_prime(a), f_double_prime(b));

        // Вывод аналитической формы только для n=2
        if (n == 2) {
            std::cout << "\n[n = 2] Аналитическое представление:\n";
            print_analytical_form("Равномерная сетка:", nodes_reg, coeffs_reg);
            print_analytical_form("Чебышевская сетка:", nodes_cheb, coeffs_cheb);
        }
    }
}

int main() {
    double a = -3.0;
    double b = 3.0;

    run_task("f1: x * cosh(x)", f1, f1_double, a, b);
    run_task("f2: |2x - 1|", f2, f2_double, a, b);

    return 0;
}
