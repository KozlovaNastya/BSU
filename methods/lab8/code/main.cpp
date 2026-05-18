#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "functions.h"

int main() {
    double x0 = 1.0, u0 = 1.0, x_end = 2.0;
    double h = 0.1;

    auto rk = rungeKuttaButcher(x0, u0, x_end, h);
    auto adams = adams4(x0, u0, x_end, h);

    std::ofstream out("results.txt");
    out << "x\tu_RK\tu_Adams\tu_Exact\tDiff\n";

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "X\t\tRK\t\tAdams\t\tExact\n";

    for (size_t i = 0; i < rk.size(); ++i) {
        double exact = exact_sol(rk[i].x);
        double diff = std::abs(rk[i].u - adams[i].u);

        std::cout << rk[i].x << "\t" << rk[i].u << "\t" << adams[i].u << "\t" << exact << "\n";
        out << rk[i].x << "\t" << rk[i].u << "\t" << adams[i].u << "\t" << exact << "\t" << diff << "\n";
    }

    out.close();
    std::cout << "\nРезультаты записаны в файл results.txt для построения графиков!\n";
    return 0;
}
