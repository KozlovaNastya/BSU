#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int n;

public:
    Matrix(int size);

    double& operator()(int i, int j) { return data[i][j]; }
    const double& operator()(int i, int j) const { return data[i][j]; }

    void generate(int studentNumber);
    std::vector<double> multiply(const std::vector<double>& vec) const;
    std::vector<double> getDiagonal() const;
    std::vector<std::vector<double>> getLowerTriangular() const;
    std::vector<std::vector<double>> getUpperTriangular() const;

    double getElement(int i, int j) const { return data[i][j]; }
    int getSize() const { return n; }

    void print() const;
};

#endif