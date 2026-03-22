#include "interpolation.h"
#include <cmath>

void generateNode(std::vector<double>& nodes, double a, double b) {
    int n = nodes.size() - 1;
    for (int i = 0; i <= n; i++) {
        nodes[i] = a + i * (b - a) / n;
    }
}

void generateChebishNodes(std::vector<double>& nodes, double a, double b) {
    int n = nodes.size() - 1;
    for (int i = 0; i <= n; i++) {
        nodes[i] = (a + b) / 2.0 + (b - a) / 2.0 * cos((2.0 * i + 1.0) * PI / (2.0 * (n + 1.0)));
    }
}

void calculateRazdRaznosti(const std::vector<double>& x, std::vector<double>& coeffs, const std::vector<double>& y_values) {
    int n = x.size();
    std::vector<double> res = y_values;
    coeffs.clear();
    coeffs.push_back(res[0]);

    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            res[i] = (res[i] - res[i - 1]) / (x[i] - x[i - j]);
        }
        coeffs.push_back(res[j]);
    }
}



double evaluateNewton(double x_val, const std::vector<double>& x_nodes, const std::vector<double>& coefficients) {
    int n = x_nodes.size();
    double result = coefficients[0];
    double product = 1.0;
    for (int k = 1; k < n; k++) {
        product *= (x_val - x_nodes[k - 1]);
        result += coefficients[k] * product;
    }
    return result;
}

std::vector<SplineSegment> buildSpline(const std::vector<double>& x, const std::vector<double>& y, double f_double_prime_a, double f_double_prime_b) {
    int n = x.size() - 1;
    std::vector<SplineSegment> s(n + 1);
    double h = x[1] - x[0];

    std::vector<double> alpha(n), beta(n);

    s[0].c = f_double_prime_a;
    s[n].c = f_double_prime_b;

    alpha[0] = 0;
    beta[0] = s[0].c;

    for (int i = 1; i < n; i++) {
        double C = 4.0 * h;
        double A = h, B = h;
        double F = 6.0 * ((y[i + 1] - y[i]) / h - (y[i] - y[i - 1]) / h);
        alpha[i] = -B / (A * alpha[i - 1] + C);
        beta[i] = (F - A * beta[i - 1]) / (A * alpha[i - 1] + C);
    }

    for (int i = n - 1; i > 0; i--) {
        s[i].c = alpha[i] * s[i + 1].c + beta[i];
    }

    for (int i = 1; i <= n; i++) {
        s[i].x = x[i];
        s[i].a = y[i];
        s[i].d = (s[i].c - s[i - 1].c) / h;
        s[i].b = h * s[i].c / 2.0 - h * h * s[i].d / 6.0 + (y[i] - y[i - 1]) / h;
    }
    return s;
}

double evaluateSpline(double x_val, const std::vector<SplineSegment>& splines) {
    int n = splines.size() - 1;
    SplineSegment s;

    if (x_val <= splines[1].x) s = splines[1];
    else {
        for (int i = 1; i <= n; i++) {
            if (x_val <= splines[i].x || i == n) {
                s = splines[i];
                break;
            }
        }
    }
    double dx = x_val - s.x;
    return s.a + s.b * dx + (s.c / 2.0) * dx * dx + (s.d / 6.0) * dx * dx * dx;
}

