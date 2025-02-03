#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
class matrix{
private:
	int m, n;
	double** p;
	//вспомогательные функции
	void allocateMemory();
	void copyValues(const matrix& other);
	void deallocateMemory();
public:
	//коснтруктор по умолчанию
	matrix();
	// конструктор с параметрами
	matrix(int m, int n, double** pp = nullptr);
	// конструктор копирования
	matrix(const matrix& other); 
	//деструктор
	~matrix(); 
	//оператор присваивания
	matrix& operator = (const matrix& other);
	//составные операторы присваивания
	matrix& operator += (const matrix& other);
	matrix& operator -= (const matrix& other);
	//умножение на константу слева
	matrix operator * (int other) const;
	//деление на константу
	matrix operator / (int other) const;
	//умножение на константу справа
	friend matrix operator * (int num, const matrix& other);
	//сложение матриц
	matrix operator + (const matrix& other) const;
	//вычитание матриц
	matrix operator - (const matrix& other) const;
	//умножение матриц
	matrix operator * (const matrix& other) const;
	//сравнение матриц на равенство и неравенство
	bool operator == (const matrix& other) const;
	//симметрия
	bool isSymmetric() const;
	//ввод и вывод матрицы в удобном для пользователя виде
	friend ostream& operator << (ostream& os, const matrix& other);

	static matrix generateRandomMatrix(int rows, int cols, int minValue = -5, int maxValue = 10);
	static matrix inputMatrix(int rows, int cols);
};
#endif