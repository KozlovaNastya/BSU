#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	int n;
	cout << "Введите размерность:" << endl;
	cin >> n;
	int** A{ new int* [n] {} };
	int** B{ new int* [n] {} };
	int** C{ new int* [n] {} };
	//матрица А
	for (int i = 0; i < n; i++) {
		A[i] = new int[i+1] {};
	}
	//матрица B
	for (int i = 0; i < n; i++) {
		B[i] = new int[n - i] {};
	}
	//матрица С
	for (int i = 0; i < n; i++) {
		C[i] = new int[n] {};
	}
	//матрица A
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 1 + i; j++)
			A[i][j] = i + 1;
	}
	cout << "Нижний левый треугольник A матрицы:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 1 + i; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	//матрица B
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++)
			B[i][j] = n - i;
	}
	cout << "Верхний левый треугольник B матрицы:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++)
			cout << B[i][j] << " ";
		cout << endl;
	}
	//матрица С
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			C[i][j] = 0;
	}
	cout << "Наложение матриц A и B:" << endl;
	//наложение матриц
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i + 1; j++) {
			C[i][j] = A[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			C[i][j] = C[i][j] + B[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << C[i][j] << " ";
		cout << endl;
	}
	//очистка
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