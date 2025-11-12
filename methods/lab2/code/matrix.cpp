#include "matrix.h"
#include <iostream>
#include <cmath>

Matrix::Matrix(int size) : n(size) {
    data.resize(n, std::vector<double>(n, 0.0));
}

void Matrix::generate(int studentNumber) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                data[i][j] = 12 * pow(i + 1, 0.6);
            }
            else {
                data[i][j] = -0.1 / pow((i + 1) * (j + 1), 0.3);
            }
        }
    }
}

std::vector<double> Matrix::multiply(const std::vector<double>& vec) const {
    std::vector<double> result(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += data[i][j] * vec[j];
        }
    }
    return result;
}

std::vector<double> Matrix::getDiagonal() const {
    std::vector<double> diag(n);
    for (int i = 0; i < n; i++) {
        diag[i] = data[i][i];
    }
    return diag;
}

std::vector<std::vector<double>> Matrix::getLowerTriangular() const {
    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            L[i][j] = data[i][j];
        }
    }
    return L;
}

std::vector<std::vector<double>> Matrix::getUpperTriangular() const {
    std::vector<std::vector<double>> U(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            U[i][j] = data[i][j];
        }
    }
    return U;
}

void Matrix::print() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}