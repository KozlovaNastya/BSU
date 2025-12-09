#ifndef EIGEN_SOLVER_H
#define EIGEN_SOLVER_H

#include "matrix.h"
#include <vector>
#include <utility>

// Константы
extern const double EPS;

// Вспомогательные функции для векторов
double vectorNorm(const std::vector<double>& v);
std::vector<double> normalize(const std::vector<double>& v);
double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2);

// Функции для вычисления собственных значений
Matrix hessenbergForm(const Matrix& A);
std::pair<Matrix, Matrix> qrDecompositionHessenberg(const Matrix& H);
std::pair<std::vector<double>, int> qrAlgorithm(const Matrix& A);
std::pair<std::pair<double, std::vector<double>>, int> powerMethod(const Matrix& A);

#endif