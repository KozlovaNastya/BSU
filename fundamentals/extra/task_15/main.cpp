#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, ".1251");
    int n;
    cout << "Enter the size:" << endl;
    cin >> n;

    int** A{ new int* [n] {} };
    int** B{ new int* [n] {} };
    int** C{ new int* [n] {} };

    // Matrix A
    for (int i = 0; i < n; i++) {
        A[i] = new int[i+1] {};
    }

    // Matrix B
    for (int i = 0; i < n; i++) {
        B[i] = new int[n - i] {};
    }

    // Matrix C
    for (int i = 0; i < n; i++) {
        C[i] = new int[n] {};
    }

    // Initialize matrix A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1 + i; j++)
            A[i][j] = i + 1;
    }

    cout << "Initialized triangular matrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1 + i; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }

    // Initialize matrix B
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++)
            B[i][j] = n - i;
    }

    cout << "Initialized triangular matrix B:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++)
            cout << B[i][j] << " ";
        cout << endl;
    }

    // Initialize matrix C
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            C[i][j] = 0;
    }

    cout << "Resultant matrix after A and B addition:" << endl;
    
    // Copy values from matrix A to C
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i + 1; j++) {
            C[i][j] = A[i][j];
        }
    }

    // Add matrix B to matrix C
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            C[i][j] = C[i][j] + B[i][j];
        }
    }

    // Output matrix C (resultant)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }

    // Deallocation
    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;

    for (int i = 0; i < n; i++)
        delete[] B[i];
    delete[] B;

    for (int i = 0; i < n; i++)
        delete[] C[i];
    delete[] C;

    return 0;
}
