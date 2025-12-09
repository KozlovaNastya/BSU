#include "matrix.h"
#include "eigen_solver.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

int main() {
    const int n = 12;

    std::cout << "================================================" << std::endl;
    std::cout << "Lab 3: Eigenvalue Problems Solution" << std::endl;
    std::cout << "================================================" << std::endl << std::endl;

    std::cout << "1. Generating symmetric matrix A of size " << n << std::endl;
    Matrix A(n);
    A.generateRandomSymmetric();
    A.saveToFile("matrix_A.txt");
    std::cout << "Matrix A saved to file matrix_A.txt" << std::endl << std::endl;

    std::cout << "First 5 rows and columns of matrix A:" << std::endl;
    for (int i = 0; i < std::min(5, n); i++) {
        for (int j = 0; j < std::min(5, n); j++) {
            std::cout << std::setw(10) << A(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "2. QR algorithm (without shift) with Hessenberg form reduction" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    auto qrResult = qrAlgorithm(A);
    std::vector<double> eigenvaluesQR = qrResult.first;
    int iterQR = qrResult.second;

    std::cout << "Number of iterations: " << iterQR << std::endl;
    std::cout << "Found eigenvalues:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "lambda" << i + 1 << " = " << std::fixed << std::setprecision(6) << eigenvaluesQR[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "3. Power method" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    auto pmResult = powerMethod(A);
    double lambdaPM = pmResult.first.first;
    std::vector<double> eigenvectorPM = pmResult.first.second;
    int iterPM = pmResult.second;

    std::cout << "Number of iterations: " << iterPM << std::endl;
    std::cout << "Largest eigenvalue by absolute value: lambda = "
        << std::fixed << std::setprecision(6) << lambdaPM << std::endl;

    std::cout << "Corresponding eigenvector (first 5 components):" << std::endl;
    for (int i = 0; i < std::min(5, n); i++) {
        std::cout << "x[" << i << "] = " << eigenvectorPM[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "4. Results comparison" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::cout << "Largest eigenvalue by QR algorithm: " << eigenvaluesQR[0] << std::endl;
    std::cout << "Largest eigenvalue by power method: " << lambdaPM << std::endl;
    std::cout << "Difference: " << fabs(eigenvaluesQR[0] - lambdaPM) << std::endl;
    std::cout << std::endl;

    std::cout << "5. Accuracy check for power method" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::vector<double> Ax = A.multiply(eigenvectorPM);
    double normDiff = 0.0;

    for (int i = 0; i < n; i++) {
        double diff = Ax[i] - lambdaPM * eigenvectorPM[i];
        normDiff += diff * diff;
    }
    normDiff = sqrt(normDiff);

    std::cout << "||A*x - lambda*x|| = " << normDiff << std::endl;
    std::cout << "Required precision epsilon = " << EPS << std::endl;

    if (normDiff < EPS) {
        std::cout << "Precision achieved!" << std::endl;
    }
    else {
        std::cout << "Precision NOT achieved!" << std::endl;
    }
    return 0;
}