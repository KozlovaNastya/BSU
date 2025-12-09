#include "eigen_solver.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

const double EPS = 1e-4;

// Вспомогательные функции для векторов
double vectorNorm(const std::vector<double>& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += val * val;
    }
    return sqrt(sum);
}

std::vector<double> normalize(const std::vector<double>& v) {
    double norm = vectorNorm(v);
    std::vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = v[i] / norm;
    }
    return result;
}

double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2) {
    double result = 0.0;
    for (size_t i = 0; i < v1.size(); i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Приведение к форме Хессенберга методом Хаусхолдера
Matrix hessenbergForm(const Matrix& A) {
    int n = A.size();
    Matrix H = A;

    for (int k = 0; k < n - 2; k++) {
        double sigma = 0.0;
        for (int i = k + 1; i < n; i++) {
            sigma += H(i, k) * H(i, k);
        }

        if (sigma < 1e-20) continue;

        double alpha = sqrt(sigma);
        if (H(k + 1, k) < 0) {
            alpha = -alpha;
        }

        std::vector<double> v(n - k - 1, 0.0);
        v[0] = H(k + 1, k) + alpha;

        for (int i = k + 2; i < n; i++) {
            v[i - k - 1] = H(i, k);
        }

        double vtv = 0.0;
        for (double vi : v) {
            vtv += vi * vi;
        }

        if (vtv < 1e-20) continue;
        double beta = 2.0 / vtv;

        for (int j = k; j < n; j++) {
            double dot = 0.0;
            for (int i = 0; i < n - k - 1; i++) {
                dot += v[i] * H(k + 1 + i, j);
            }
            for (int i = 0; i < n - k - 1; i++) {
                H(k + 1 + i, j) -= beta * v[i] * dot;
            }
        }

        for (int i = 0; i < n; i++) {
            double dot = 0.0;
            for (int j = 0; j < n - k - 1; j++) {
                dot += H(i, k + 1 + j) * v[j];
            }
            for (int j = 0; j < n - k - 1; j++) {
                H(i, k + 1 + j) -= beta * dot * v[j];
            }
        }
    }

    for (int i = 2; i < n; i++) {
        for (int j = 0; j < i - 1; j++) {
            H(i, j) = 0.0;
        }
    }

    return H;
}

// QR-разложение матрицы Хессенберга (алгоритм Гивенса)
std::pair<Matrix, Matrix> qrDecompositionHessenberg(const Matrix& H) {
    int n = H.size();
    Matrix Q(n);
    Matrix R = H;

    for (int i = 0; i < n; i++) {
        Q(i, i) = 1.0;
    }

    for (int i = 0; i < n - 1; i++) {
        double a = R(i, i);
        double b = R(i + 1, i);
        double r = sqrt(a * a + b * b);

        if (fabs(r) < 1e-20) continue;

        double c = a / r;
        double s = -b / r;

        for (int j = i; j < n; j++) {
            double temp1 = R(i, j);
            double temp2 = R(i + 1, j);
            R(i, j) = c * temp1 - s * temp2;
            R(i + 1, j) = s * temp1 + c * temp2;
        }

        R(i + 1, i) = 0.0;

        for (int j = 0; j < n; j++) {
            double temp1 = Q(j, i);
            double temp2 = Q(j, i + 1);
            Q(j, i) = c * temp1 - s * temp2;
            Q(j, i + 1) = s * temp1 + c * temp2;
        }
    }

    return std::make_pair(Q, R);
}

// QR-алгоритм без сдвига
std::pair<std::vector<double>, int> qrAlgorithm(const Matrix& A) {
    int n = A.size();
    Matrix H = hessenbergForm(A);
    Matrix Ak = H;
    int iterations = 0;
    const int maxIterations = 1000;

    std::vector<double> prevDiagonal(n, 0.0);
    for (int i = 0; i < n; i++) {
        prevDiagonal[i] = Ak(i, i);
    }

    while (iterations < maxIterations) {
        std::pair<Matrix, Matrix> qrResult = qrDecompositionHessenberg(Ak);
        Matrix Q = qrResult.first;
        Matrix R = qrResult.second;

        Matrix nextAk(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0.0;
                for (int k = 0; k < n; k++) {
                    sum += R(i, k) * Q(k, j);
                }
                nextAk(i, j) = sum;
            }
        }

        Ak = nextAk;
        iterations++;

        double maxChange = 0.0;
        for (int i = 0; i < n; i++) {
            double change = fabs(Ak(i, i) - prevDiagonal[i]);
            if (change > maxChange) {
                maxChange = change;
            }
            prevDiagonal[i] = Ak(i, i);
        }

        double maxSubDiag = 0.0;
        for (int i = 1; i < n; i++) {
            double subDiag = fabs(Ak(i, i - 1));
            if (subDiag > maxSubDiag) {
                maxSubDiag = subDiag;
            }
        }

        if ((maxSubDiag < EPS * 10) || (maxChange < EPS * 10 && iterations > 10)) {
            break;
        }

        if (iterations < 10) continue;
    }

    std::vector<double> eigenvalues(n);
    for (int i = 0; i < n; i++) {
        eigenvalues[i] = Ak(i, i);
    }

    std::sort(eigenvalues.begin(), eigenvalues.end(),
        [](double a, double b) { return fabs(a) > fabs(b); });

    return std::make_pair(eigenvalues, iterations);
}

// Степенной метод
std::pair<std::pair<double, std::vector<double>>, int> powerMethod(const Matrix& A) {
    int n = A.size();
    int iterations = 0;
    const int maxIterations = 10000;

    
    std::vector<double> x(n, 1.0);
    x = normalize(x);

    double lambda = 0.0;
    double lambdaPrev = 0.0;
    double error = 1.0;

    while (iterations < maxIterations) {
        lambdaPrev = lambda;

        std::vector<double> Ax = A.multiply(x);

        double numerator = 0.0;
        double denominator = 0.0;
        for (int i = 0; i < n; i++) {
            numerator += x[i] * Ax[i];
            denominator += x[i] * x[i];
        }
        lambda = numerator / denominator;

        double norm = vectorNorm(Ax);
        if (norm > 1e-20) {
            for (int i = 0; i < n; i++) {
                x[i] = Ax[i] / norm;
            }
        }

        iterations++;

        std::vector<double> AxCurrent = A.multiply(x);
        error = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = AxCurrent[i] - lambda * x[i];
            error += diff * diff;
        }
        error = sqrt(error);

        if (error < EPS) {
            break;
        }

        if (iterations > 10 && fabs(lambda - lambdaPrev) < EPS * 0.01 && error < EPS * 10) {
            for (int extra = 0; extra < 100 && error >= EPS; extra++) {
                std::vector<double> Ax = A.multiply(x);

                double num = 0.0, den = 0.0;
                for (int i = 0; i < n; i++) {
                    num += x[i] * Ax[i];
                    den += x[i] * x[i];
                }
                lambda = num / den;

                norm = vectorNorm(Ax);
                if (norm > 1e-20) {
                    for (int i = 0; i < n; i++) {
                        x[i] = Ax[i] / norm;
                    }
                }

                iterations++;

                AxCurrent = A.multiply(x);
                error = 0.0;
                for (int i = 0; i < n; i++) {
                    double diff = AxCurrent[i] - lambda * x[i];
                    error += diff * diff;
                }
                error = sqrt(error);

                if (error < EPS) break;
            }
            break;
        }
    }

    std::vector<double> AxFinal = A.multiply(x);
    double lambdaFinal = 0.0;
    double normXFinal = 0.0;
    for (int i = 0; i < n; i++) {
        lambdaFinal += x[i] * AxFinal[i];
        normXFinal += x[i] * x[i];
    }
    lambdaFinal /= normXFinal;

    double finalError = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = AxFinal[i] - lambdaFinal * x[i];
        finalError += diff * diff;
    }
    finalError = sqrt(finalError);

    if (finalError >= EPS && iterations < maxIterations) {
        int extraIterations = 0;
        while (extraIterations < 1000 && finalError >= EPS) {
            std::vector<double> Ax = A.multiply(x);

            lambdaFinal = 0.0;
            normXFinal = 0.0;
            for (int i = 0; i < n; i++) {
                lambdaFinal += x[i] * Ax[i];
                normXFinal += x[i] * x[i];
            }
            lambdaFinal /= normXFinal;

            double norm = vectorNorm(Ax);
            if (norm > 1e-20) {
                for (int i = 0; i < n; i++) {
                    x[i] = Ax[i] / norm;
                }
            }

            iterations++;
            extraIterations++;

            AxFinal = A.multiply(x);
            finalError = 0.0;
            for (int i = 0; i < n; i++) {
                double diff = AxFinal[i] - lambdaFinal * x[i];
                finalError += diff * diff;
            }
            finalError = sqrt(finalError);
        }
    }

    return std::make_pair(std::make_pair(lambdaFinal, x), iterations);
}