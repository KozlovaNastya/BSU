#include "iterative.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

IterativeMethods::IterativeMethods(int size, int studentNum)
    : A(size), n(size), studentNumber(studentNum) {
    b.resize(n);
    exactSolution.resize(n);
    generateSystem();
}

void IterativeMethods::generateSystem() {
    for (int i = 0; i < n; i++) {
        exactSolution[i] = studentNumber + i;
    }

    A.generate(studentNumber);

    b = A.multiply(exactSolution);
}

std::vector<double> IterativeMethods::simpleIteration(double epsilon, int& iterations) {
    std::vector<double> x(n, 1.0);
    std::vector<double> diag = A.getDiagonal();

    last_x_prev = std::vector<double>(n, 1.0);

    iterations = 0;
    double posterior_error;

    do {
        last_x_prev = x;

        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A.getElement(i, j) * last_x_prev[j];
                }
            }
            x[i] = (b[i] - sum) / diag[i];
        }

        last_x_curr = x;

        posterior_error = calculatePosteriorError(last_x_prev, last_x_curr);

        iterations++;

    } while (posterior_error > epsilon && iterations < 10000);

    return x;
}

std::vector<double> IterativeMethods::seidelMethod(int maxIterations) {
    std::vector<double> x(n, 1.0);
    std::vector<double> diag = A.getDiagonal();

    for (int k = 0; k < maxIterations; k++) {
        for (int i = 0; i < n; i++) {
            double sum_before = 0.0;
            double sum_after = 0.0;

            for (int j = 0; j < i; j++) {
                sum_before += A.getElement(i, j) * x[j];
            }

            for (int j = i + 1; j < n; j++) {
                sum_after += A.getElement(i, j) * x[j];
            }

            x[i] = (b[i] - sum_before - sum_after) / diag[i];
        }
    }

    return x;
}

std::vector<double> IterativeMethods::relaxationMethod(double omega, int maxIterations) {
    std::vector<double> x(n, 1.0);
    std::vector<double> diag = A.getDiagonal();

    for (int k = 0; k < maxIterations; k++) {
        for (int i = 0; i < n; i++) {
            double sum_before = 0.0;
            double sum_after = 0.0;

            for (int j = 0; j < i; j++) {
                sum_before += A.getElement(i, j) * x[j];
            }

            for (int j = i + 1; j < n; j++) {
                sum_after += A.getElement(i, j) * x[j];
            }

            double temp = (b[i] - sum_before - sum_after) / diag[i];
            x[i] = (1 - omega) * x[i] + omega * temp;
        }
    }

    return x;
}

double IterativeMethods::calculateError(const std::vector<double>& solution) const {
    double error = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = solution[i] - exactSolution[i];
        error += diff * diff;
    }
    return std::sqrt(error);
}

void IterativeMethods::printVector(const std::vector<double>& vec) const {
    std::cout << std::fixed << std::setprecision(6);
    for (int i = 0; i < std::min(10, n); i++) {
        std::cout << vec[i] << " ";
    }
    if (n > 10) {
        std::cout << "...";
    }
    std::cout << std::endl;
}

double IterativeMethods::calculateMatrixNorm(const Matrix& mat) const {
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        double row_sum = 0.0;
        for (int j = 0; j < n; j++) {
            row_sum += std::abs(mat.getElement(i, j));
        }
        norm = std::max(norm, row_sum);
    }
    return norm;
}

int IterativeMethods::calculatePriorIterations(double epsilon) const {

    Matrix B(n);
    std::vector<double> diag = A.getDiagonal();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                B(i, j) = 0.0;
            }
            else {
                B(i, j) = -A.getElement(i, j) / diag[i];
            }
        }
    }

    double B_norm = calculateMatrixNorm(B);

    std::vector<double> x0(n, 1.0);

    std::vector<double> x1(n);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += B.getElement(i, j) * x0[j];
        }
        x1[i] = sum + b[i] / diag[i];
    }

    double diff_norm = 0.0;
    for (int i = 0; i < n; i++) {
        diff_norm += (x1[i] - x0[i]) * (x1[i] - x0[i]);
    }
    diff_norm = std::sqrt(diff_norm);

    if (B_norm >= 1.0 || B_norm == 0.0) {
        return 1000;
    }

    double numerator = std::log(epsilon * (1 - B_norm) / diff_norm);
    double denominator = std::log(B_norm);

    int k_prior = static_cast<int>(std::ceil(numerator / denominator));
    return std::max(1, k_prior);
}

double IterativeMethods::calculatePosteriorError(const std::vector<double>& x_prev,
    const std::vector<double>& x_curr) const {
    Matrix B(n);
    std::vector<double> diag = A.getDiagonal();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                B(i, j) = 0.0;
            }
            else {
                B(i, j) = -A.getElement(i, j) / diag[i];
            }
        }
    }

    double B_norm = calculateMatrixNorm(B);

    double diff_norm = 0.0;
    for (int i = 0; i < n; i++) {
        diff_norm += (x_curr[i] - x_prev[i]) * (x_curr[i] - x_prev[i]);
    }
    diff_norm = std::sqrt(diff_norm);

    return (B_norm / (1 - B_norm)) * diff_norm;
}

double IterativeMethods::getBNorm() const {
    Matrix B(n);
    std::vector<double> diag = A.getDiagonal();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                B(i, j) = 0.0;
            }
            else {
                B(i, j) = -A.getElement(i, j) / diag[i];
            }
        }
    }

    return calculateMatrixNorm(B);
}

std::vector<double> IterativeMethods::getVectorB() const {
    return b;
}