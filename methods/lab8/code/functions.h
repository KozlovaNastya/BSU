#pragma once
#include <vector>

double f(double x, double u);

double exact_sol(double x);

struct Point {
    double x;
    double u;
};

std::vector<Point> rungeKuttaButcher(double x0, double u0, double x_end, double h);

std::vector<Point> adams4(double x0, double u0, double x_end, double h);
