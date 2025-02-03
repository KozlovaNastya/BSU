#include "matrix.h"
// Вспомогательная функция для выделения памяти
void matrix::allocateMemory() {
	p = new double* [m];
	for (int i = 0; i < m; ++i) {
		p[i] = new double[n] {};
	}
}

// Вспомогательная функция для копирования значений
void matrix::copyValues(const matrix& other) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			p[i][j] = other.p[i][j];
		}
	}
}

// Вспомогательная функция для освобождения памяти
void matrix::deallocateMemory() {
	for (int i = 0; i < m; ++i) {
		delete[] p[i];
	}
	delete[] p;
}
matrix::matrix() : m(0), n(0), p(nullptr) {}
matrix::matrix(int rows, int cols, double** pp) : m(rows), n(cols) {
	if (m <= 0 || n <= 0) {
		throw invalid_argument("Matrix dimensions must be greater than 0.");
	}
	allocateMemory();
	if (pp) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				p[i][j] = pp[i][j];
			}
		}
	}
}
matrix::matrix(const matrix& other) : m(other.m), n(other.n) {
	allocateMemory();
	copyValues(other);
}
matrix& matrix::operator = (const matrix& other) {
	if (this != &other) {
		deallocateMemory();
		m = other.m;
		n = other.n;
		allocateMemory();
		copyValues(other);
	}
	return *this;
};
matrix& matrix::operator += (const matrix& other) {
	if (m != other.m || n != other.n) {
		throw invalid_argument("Matrix dimensions must match for addition.");
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			p[i][j] += other.p[i][j];
		}
	}
	return *this;
};
matrix& matrix::operator -= (const matrix& other) {
	if (m != other.m || n != other.n) {
		throw invalid_argument("Matrix dimensions must match for subtraction.");
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			p[i][j] -= other.p[i][j];
		}
	}
	return *this;
};
matrix matrix::operator * (int other) const {
	matrix result(m, n, nullptr);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			result.p[i][j] = p[i][j] * other;
		}
	}
	return result;
};
matrix matrix::operator / (int other) const {
	if (other == 0) {
		throw invalid_argument("Division by zero.");
	}
	matrix result(m, n, nullptr);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			result.p[i][j] = p[i][j] / other;
		}
	}
	return result;
};
matrix operator * (int num, const matrix& other){
	matrix result(other.m, other.n, nullptr);
	for (int i = 0; i < other.m; ++i) {
		for (int j = 0; j < other.n; ++j) {
				result.p[i][j] = num * other.p[i][j];
			}
	}
	return result;
};
matrix matrix::operator + (const matrix& other) const {
	if (m != other.m || n != other.n) {
		throw invalid_argument("Matrix dimensions must match for addition.");
	}
	matrix result(m, n, nullptr);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			result.p[i][j] = p[i][j] + other.p[i][j];
		}
	}
	return result;
}
matrix matrix::operator - (const matrix& other) const {
	if (m != other.m || n != other.n) {
		throw invalid_argument("Matrix dimensions must match for subtraction.");
	}
	matrix result(m, n, nullptr);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			result.p[i][j] = p[i][j] - other.p[i][j];
		}
	}
	return result;
};
matrix matrix::operator * (const matrix& other) const {
	if (n != other.m) {
		throw invalid_argument("Matrix dimensions must match for multiplication.");
	}
	matrix result(m, other.n, nullptr);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < other.n; ++j) {
			result.p[i][j] = 0;
			for (int k = 0; k < n; ++k) {
				result.p[i][j] += p[i][k] * other.p[k][j];
			}
		}
	}
	return result;
}
bool matrix::operator == (const matrix& other) const {
	if (m != other.m || n != other.n) {
		return false;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (p[i][j] != other.p[i][j]) {
				return false;
			}
		}
	}
	return true;
};
bool matrix::isSymmetric() const {
	if (m != n) {
		return false;
	}
	for (int i = 0; i < m; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (p[i][j] != p[j][i]) {
				return false;
			}
		}
	}
	return true;
}

ostream& operator << (ostream& os, const matrix& other) {
	for (int i = 0; i < other.m; i++) {
		for (int j = 0; j < other.n; j++)
			os << other.p[i][j] << ' ';
		os << endl;
	}
	return os;
};

matrix matrix::generateRandomMatrix(int rows, int cols, int minValue, int maxValue) {
	matrix result(rows, cols, nullptr);
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			result.p[i][j] = minValue + rand() % (maxValue - minValue + 1);
		}
	}
	return result;
}

matrix matrix::inputMatrix(int rows, int cols) {
	matrix result(rows, cols, nullptr);
	cout << "Enter matrix elements row by row:\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> result.p[i][j];
		}
	}
	return result;
}

matrix::~matrix() {
	if (p) {
		for (int i = 0; i < m; ++i)
			delete[] p[i];
		delete[] p;
	}
}