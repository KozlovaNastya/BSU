#include <iostream>
#include <ctime>
using namespace std;
int main() {
	int n, S;
	cin >> n;
	srand(0);
	setlocale(LC_ALL, ".1251");
//выделение памяти
	int** A = new int*[n];
	for (int i = 0; i < n; i++)
		A[i] = new int[n];
//задание матрицы
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = rand() % 100;
//вывод матрицы
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
//след матрицы
	S = 0;
	for (int i = 0; i < n; i++)
		S = S + A[i][i];
	cout << "След матрицы " << S << endl;
	S = 0;
//счет верхнего левого треугольника
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n-i; j++)
			S = S + A[i][j];
	cout << "Сумма верхнего левого треугольника = " << S << endl;
//очищение памяти
	for (int i = 0; i < n; i++)
		delete[] A[i];
	delete[] A;
	return 0;
}