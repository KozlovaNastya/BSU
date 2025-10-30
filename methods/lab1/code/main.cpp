#include "MarixSolver.h"


int main() {
    const int N = 15;
    MatrixSolver solver(N);

    cout << "Solution for matrix " << N << "x" << N << endl;

    // Метод Гаусса с выбором ведущего элемента
    cout << "\n1. GAUSSIAN METHOD WITH CHOICE OF THE LEADING ELEMENT" << endl;
    double determinant;
    vector<double> x_gauss = solver.gaussWithPivot(determinant);

    solver.printVector(x_gauss, "Solution x");
    cout << "A Determinant: " << scientific << setprecision(10) << determinant << endl;
    cout << "Norm of residual ||Ax - b||∞: " << scientific << solver.residualNorm(x_gauss) << endl;

    // Метод вращений (QR-разложение)
    cout << "\n2. ROTATION METHOD (QR DECOMPOSITION)" << endl;
    vector<vector<double>> Q, R;
    vector<double> x_qr = solver.rotationMethod(Q, R);

    solver.printVector(x_qr, "Solution x");
    cout << "Norm of residual ||Ax - b||: " << scientific << solver.residualNorm(x_qr) << endl;

    // Проверка QR-разложения
    double qr_error = solver.checkQRDecomposition(Q, R);
    cout << "Error QR decomposition ||A - QR||: " << scientific << qr_error << endl;

    // Проверка ортогональности Q
    double ortho_error = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            double dot = 0.0;
            for (int k = 0; k < N; k++) {
                dot += Q[k][i] * Q[k][j]; // Q^T * Q
            }
            if (i == j) {
                ortho_error = max(ortho_error, fabs(dot - 1.0));
            }
            else {
                ortho_error = max(ortho_error, fabs(dot));
            }
        }
    }
    cout << "Orthogonality error ||Q^TQ - I||: " << scientific << ortho_error << endl;

    return 0;
}