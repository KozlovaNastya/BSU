#include "matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <algorithm>

Matrix::Matrix(int size) : n(size), data(size, std::vector<double>(size, 0.0)) {}

int Matrix::size() const { return n; }

double& Matrix::operator()(int i, int j) { return data[i][j]; }

const double& Matrix::operator()(int i, int j) const { return data[i][j]; }

void Matrix::generateRandomSymmetric() {
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double value = (rand() % 100) / 10.0;
            data[i][j] = value;
            if (i != j) {
                data[j][i] = value;
            }
        }
    }

    // Убедимся, что матрица не диагональная и не трехдиагональная
    for (int i = 0; i < std::min(n, 3); i++) {
        for (int j = i + 3; j < n; j++) {
            double value = (rand() % 50 + 1) / 100.0;
            data[i][j] = value;
            data[j][i] = value;
        }
    }
}

void Matrix::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    file << std::fixed << std::setprecision(6);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << data[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
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