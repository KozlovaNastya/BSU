#include "MarixSolver.h"

using namespace std;

// Конструктор
MatrixSolver::MatrixSolver(int n) : N(n) {
    A.resize(N, vector<double>(N, 0.0));
    b.resize(N, 0.0);
    initializeMatrix();
}

// Инициализация матрицы A и вектора b согласно варианту
void MatrixSolver::initializeMatrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                A[i][j] = 5.0 * sqrt(i);
            }
            else {
                A[i][j] = sqrt(i) - sqrt(j);
            }
        }
        b[i] = 4.5 + sqrt(i);
    }
}

// Вывод матрицы
void MatrixSolver::printMatrix(const vector<vector<double>>& mat, const string& name) {
    cout << name << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(10) << setprecision(4) << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Вывод вектора
void MatrixSolver::printVector(const vector<double>& vec, const string& name) {
    cout << name << ": ";
    for (int i = 0; i < N; i++) {
        cout << setw(10) << setprecision(6) << vec[i] << " ";
    }
    cout << endl;
}

// Норма невязки ||Ax - b||∞
double MatrixSolver::residualNorm(const vector<double>& x) {
    double maxResidual = 0.0;
    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int j = 0; j < N; j++) {
            sum += A[i][j] * x[j];
        }
        double residual = fabs(sum - b[i]);
        if (residual > maxResidual) {
            maxResidual = residual;
        }
    }
    return maxResidual;
}

// Норма Фробениуса для матрицы
double MatrixSolver::frobeniusNorm(const vector<vector<double>>& mat) {
    double norm = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            norm += mat[i][j] * mat[i][j];
        }
    }
    return sqrt(norm);
}

// Метод Гаусса с выбором ведущего элемента + определитель
vector<double> MatrixSolver::gaussWithPivot(double& determinant) {
    vector<vector<double>> A_temp = A;
    vector<double> b_temp = b;
    vector<int> col_pivot(N);  // перестановки столбцов (переменных)

    // Инициализация pivot массива для столбцов
    for (int i = 0; i < N; i++) {
        col_pivot[i] = i;
    }

    determinant = 1.0;

    // Прямой ход с полным выбором ведущего элемента
    for (int k = 0; k < N; k++) {
        // Поиск максимального элемента в подматрице
        int maxRow = k;
        int maxCol = k;
        double maxVal = fabs(A_temp[k][k]);

        for (int i = k; i < N; i++) {
            for (int j = k; j < N; j++) {
                if (fabs(A_temp[i][j]) > maxVal) {
                    maxVal = fabs(A_temp[i][j]);
                    maxRow = i;
                    maxCol = j;
                }
            }
        }

        // Перестановка строк (не влияет на порядок переменных)
        if (maxRow != k) {
            swap(A_temp[k], A_temp[maxRow]);
            swap(b_temp[k], b_temp[maxRow]);
            determinant *= -1;
        }

        // Перестановка столбцов (меняет порядок переменных - нужно отслеживать)
        if (maxCol != k) {
            for (int i = 0; i < N; i++) {
                swap(A_temp[i][k], A_temp[i][maxCol]);
            }
            swap(col_pivot[k], col_pivot[maxCol]);
            determinant *= -1;
        }

        // Проверка на вырожденность
        if (fabs(A_temp[k][k]) < 1e-12) {
            determinant = 0.0;
            return vector<double>(N, 0.0);
        }

        // Исключение
        for (int i = k + 1; i < N; i++) {
            double factor = A_temp[i][k] / A_temp[k][k];
            for (int j = k; j < N; j++) {
                A_temp[i][j] -= factor * A_temp[k][j];
            }
            b_temp[i] -= factor * b_temp[k];
        }

        determinant *= A_temp[k][k];
    }

    // Обратный ход
    vector<double> x(N, 0.0);
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b_temp[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A_temp[i][j] * x[j];
        }
        x[i] /= A_temp[i][i];
    }

    // Восстановление порядка переменных (обратная перестановка столбцов)
    vector<double> x_sorted(N);
    for (int i = 0; i < N; i++) {
        x_sorted[col_pivot[i]] = x[i];
    }

    return x_sorted;
}

// Метод вращений (QR-разложение)
vector<double> MatrixSolver::rotationMethod(vector<vector<double>>& Q, vector<vector<double>>& R) {
    Q.resize(N, vector<double>(N, 0.0));
    R = A;

    // Инициализация Q как единичной матрицы
    for (int i = 0; i < N; i++) {
        Q[i][i] = 1.0;
    }

    vector<double> b_temp = b;

    // Построение QR-разложения методом вращений
    for (int j = 0; j < N; j++) {
        for (int i = j + 1; i < N; i++) {
            if (fabs(R[i][j]) > 1e-12) {
                double r = sqrt(R[j][j] * R[j][j] + R[i][j] * R[i][j]);
                double c = R[j][j] / r;
                double s = R[i][j] / r;

                // Применение вращения к R
                for (int k = j; k < N; k++) {
                    double temp_j = R[j][k];
                    double temp_i = R[i][k];
                    R[j][k] = c * temp_j + s * temp_i;
                    R[i][k] = -s * temp_j + c * temp_i;
                }

                // Применение вращения к Q
                for (int k = 0; k < N; k++) {
                    double temp_j = Q[k][j];
                    double temp_i = Q[k][i];
                    Q[k][j] = c * temp_j + s * temp_i;
                    Q[k][i] = -s * temp_j + c * temp_i;
                }

                // Применение вращения к b
                double temp_bj = b_temp[j];
                double temp_bi = b_temp[i];
                b_temp[j] = c * temp_bj + s * temp_bi;
                b_temp[i] = -s * temp_bj + c * temp_bi;
            }
        }
    }

    // Решение системы Rx = Q^T b
    vector<double> x(N, 0.0);
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b_temp[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= R[i][j] * x[j];
        }
        x[i] /= R[i][i];
    }

    return x;
}

// Проверка QR-разложения: ||A - QR||
double MatrixSolver::checkQRDecomposition(const vector<vector<double>>& Q, const vector<vector<double>>& R) {
    vector<vector<double>> QR(N, vector<double>(N, 0.0));

    // Вычисление QR
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                QR[i][j] += Q[k][i] * R[k][j]; // Q^T * R
            }
        }
    }

    // Вычисление нормы разности ||A - QR||
    double maxDiff = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double diff = fabs(A[i][j] - QR[i][j]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }
    }

    return maxDiff;
}