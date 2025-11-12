#ifndef ITERATIVE_METHODS_H
#define ITERATIVE_METHODS_H

#include <vector>
#include "matrix.h"

class IterativeMethods {
private:
    Matrix A;
    std::vector<double> b;
    std::vector<double> exactSolution;
    int n;
    int studentNumber;
    std::vector<double> last_x_prev, last_x_curr;

public:
    IterativeMethods(int size, int studentNum);

    void generateSystem();
    std::vector<double> simpleIteration(double epsilon, int& iterations);
    std::vector<double> seidelMethod(int maxIterations);
    std::vector<double> relaxationMethod(double omega, int maxIterations);

    double calculateError(const std::vector<double>& solution) const;
    void printVector(const std::vector<double>& vec) const;
    std::vector<double> getExactSolution() const { return exactSolution; }

    double calculateMatrixNorm(const Matrix& mat) const;
    int calculatePriorIterations(double epsilon) const;
    double calculatePosteriorError(const std::vector<double>& x_prev, const std::vector<double>& x_curr) const;

    std::vector<double> getLastXPrev() const { return last_x_prev; }
    std::vector<double> getLastXCurr() const { return last_x_curr; }

    std::vector<double> getVectorB() const;
    double getBNorm() const;
};

#endif