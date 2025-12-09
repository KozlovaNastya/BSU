#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

class Matrix {
private:
    int n;
    std::vector<std::vector<double>> data;

public:
    Matrix(int size);
    int size() const;

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    void generateRandomSymmetric();
    void saveToFile(const std::string& filename) const;
    std::vector<double> multiply(const std::vector<double>& vec) const;
};

#endif