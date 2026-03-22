#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return pow(x, 4) + 4 * pow(x, 3) - 12 * pow(x, 2) + 1;
}

double df(double x) {
    return 4 * pow(x, 3) + 12 * pow(x, 2) - 24 * x;
}

double phi(double x) {
    return sqrt((pow(x, 4) + 4 * pow(x, 3) + 1) / 12.0);
}

double d_phi(double x) {
    double numerator = 4 * pow(x, 3) + 12 * pow(x, 2);
    double denominator = 24 * phi(x);
    return (phi(x) == 0) ? 0 : numerator / denominator;
}

void solve() {
    double eps = 1e-6;
    double a = 0.0, b = 1.0;

    cout << "--- simple iteration method ---" << endl;
    double q = 0.8;
    double x_prev = 0.5;
    double x_curr;
    int iter_mpi = 0;

    do {
        x_curr = phi(x_prev);
        iter_mpi++;
        if ((q / (1 - q)) * abs(x_curr - x_prev) < eps) break;
        x_prev = x_curr;
    } while (true);

    cout << "root: " << fixed << setprecision(7) << x_curr << endl;
    cout << "iterations: " << iter_mpi << endl << endl;

    cout << "--- Newton's methods ---" << endl;
    x_prev = 1.0;
    int iter_newton = 0;

    do {
        x_curr = x_prev - f(x_prev) / df(x_prev);
        iter_newton++;
        if (abs(x_curr - x_prev) < eps) break;
        x_prev = x_curr;
    } while (true);

    cout << "root: " << x_curr << endl;
    cout << "iterations: " << iter_newton << endl;
}

int main() {
    solve();
    return 0;
}
