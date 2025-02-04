#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
class matrix{
private:
	int m, n;
	double** p;
	void allocateMemory();
	void copyValues(const matrix& other);
	void deallocateMemory();
public:
	matrix();
	matrix(int m, int n, double** pp = nullptr);
	matrix(const matrix& other); 
	~matrix(); 
	matrix& operator = (const matrix& other);
	matrix& operator += (const matrix& other);
	matrix& operator -= (const matrix& other);
	matrix operator * (int other) const;
	matrix operator / (int other) const;
	friend matrix operator * (int num, const matrix& other);
	matrix operator + (const matrix& other) const;
	matrix operator - (const matrix& other) const;
	matrix operator * (const matrix& other) const;
	bool operator == (const matrix& other) const;
	bool isSymmetric() const;
	friend ostream& operator << (ostream& os, const matrix& other);

	static matrix generateRandomMatrix(int rows, int cols, int minValue = -5, int maxValue = 10);
	static matrix inputMatrix(int rows, int cols);
};
#endif
