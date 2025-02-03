#include "matrix.h"
#include <ctime>
int main() {
    srand(time(0));
    int rows = 3, cols = 3;
    double** arr = new double* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new double[cols];
        for (int j = 0; j < cols; j++)
            arr[i][j] = i + j;
    }
    matrix matrix1(rows, cols, arr);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            arr[i][j] = i - j;
    }
    matrix matrix2(rows, cols, arr);
    rows = 4;
    cols = 5;
    double** randomMatrix = new double* [rows];
    for (int i = 0; i < rows; i++) {
        randomMatrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            randomMatrix[i][j] = -5 + rand() % 16;
        }
    }
    matrix A(rows, cols, randomMatrix);
    cout << "matrix A:" << endl << A;
    matrix B = A;
    cout << "Matrix B (copy of A):" << endl << B;
    cout << "First matrix:" << endl << matrix1 << "Second matrix:" << endl << matrix2;
    matrix F = (A + (5 * B)) / 3;
    cout << "Matrix F = (A + 5 * B) / 3:" << endl << F;
    int rowsD, colsD;
    cout << "Enter the number of rows and columns for matrix D (rows must match B): ";
    cin >> rowsD >> colsD;

    if (rowsD != cols) { // Условие для возможности умножения D * B
        cerr << "Error: The number of rows in D must match the number of columns in B." << endl;
        return 1;
    }

    double** inputMatrix = new double* [rowsD];
    for (int i = 0; i < rowsD; i++) {
        inputMatrix[i] = new double[colsD];
        cout << "Enter row " << i + 1 << ": ";
        for (int j = 0; j < colsD; j++) {
            cin >> inputMatrix[i][j];
        }
    }
    matrix D(rowsD, colsD, inputMatrix);

    // Вывод матрицы D
    cout << "Matrix D:" << endl << D;

    // Вычисляем Z = D * B
    matrix Z = D * B;
    cout << "Matrix Z = D * B:" << endl << Z;

    // Вычисляем G = Z - B
    matrix G = Z - B;
    cout << "Matrix G = Z - B:" << endl << G;
    /*matrix result = matrix1 + matrix2;
    cout << "matrix1 + matrix2" << endl << result;
    result = matrix1 - matrix2;
    cout << "matrix1 - matrix2" << endl << result;
    result = matrix1 * matrix2;
    cout << "matrix1 * matrix2" << endl << result;
    cout << "matrix1 == matrix2 ? answer: ";
    cout << (matrix1 == matrix2) << endl;
    result = matrix1 * 3;
    cout << "matrix1 * 3" << endl << result;
    result = 3 * matrix1;
    cout << "3 * matrix1" << endl << result;
    result = matrix1 / 3;
    cout << "matrix1 / 3" << endl << result;
    result += matrix2;
    cout << "result += matrix2" << endl << result;
    result -= matrix2;
    cout << "result -= matrix2" << endl << result;*/
    cout << "symetric matrix2 " << matrix2.isSymmetric() << endl;

    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
    for (int i = 0; i < rows; ++i) {
        delete[] randomMatrix[i];
    }
    delete[] randomMatrix;
    randomMatrix = nullptr;
    for (int i = 0; i < rowsD; ++i) {
        delete[] inputMatrix[i];
    }
    delete[] inputMatrix;
    inputMatrix = nullptr;
	return 0;
}
