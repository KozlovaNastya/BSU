#include "functions.h"
#include <cmath>

double f(double x, double u) {
    return (x * x + 1.0) / (u * u);
}

double exact_sol(double x) {
    return std::cbrt(x * x * x + 3.0 * x - 3.0);
}

double solveK2(double x, double u, double h, double k1) {
    double k2 = k1;
    double eps = 1e-6;
    for (int i = 0; i < 100; ++i) {
        double next_u = u + 0.25 * h * k1 + 0.25 * h * k2;
        double F = k2 - f(x + 0.5 * h, next_u);

        double df_du = -2.0 * (x * x + 1.0) / (next_u * next_u * next_u);
        double dF = 1.0 - df_du * 0.25 * h;

        double delta = F / dF;
        k2 -= delta;
        if (std::abs(delta) < eps) break;
    }
    return k2;
}

std::vector<Point> rungeKuttaButcher(double x0, double u0, double x_end, double h) {
    std::vector<Point> res;
    res.push_back({ x0, u0 });

    double x = x0;
    double u = u0;

    while (x < x_end - 1e-9) {
        double k1 = f(x, u);
        double k2 = solveK2(x, u, h, k1);

        u = u + h * k2;
        x += h;
        res.push_back({ x, u });
    }
    return res;
}

std::vector<Point> adams4(double x0, double u0, double x_end, double h) {
    std::vector<Point> res;
    auto rk_start = rungeKuttaButcher(x0, u0, x0 + 3.0 * h, h);
    res = rk_start;

    int n = res.size();
    double x = x0 + 3.0 * h;

    while (x < x_end - 1e-9) {
        int i = res.size() - 1;
        double f_i = f(res[i].x, res[i].u);
        double f_i1 = f(res[i - 1].x, res[i - 1].u);
        double f_i2 = f(res[i - 2].x, res[i - 2].u);
        double f_i3 = f(res[i - 3].x, res[i - 3].u);

        double u_next = res[i].u + (h / 24.0) * (55.0 * f_i - 59.0 * f_i1 + 37.0 * f_i2 - 9.0 * f_i3);
        x += h;
        res.push_back({ x, u_next });
    }
    return res;
}
