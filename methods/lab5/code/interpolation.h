#pragma once
#include <vector>

const double PI = 3.141592653589793;

void generateNode(std::vector<double>& nodes, double a, double b);
void generateChebishNodes(std::vector<double>& nodes, double a, double b);

void calculateRazdRaznosti(const std::vector<double>& x, std::vector<double>& table, const std::vector<double>& y_values);

double evaluateNewton(double x_val, const std::vector<double>& x_nodes, const std::vector<double>& coefficients);

struct SplineSegment {
    double a, b, c, d, x;
};

std::vector<SplineSegment> buildSpline(const std::vector<double>& x, const std::vector<double>& y, double f_double_prime_a, double f_double_prime_b);

double evaluateSpline(double x_val, const std::vector<SplineSegment>& splines);

