//Козлова Анастасия 10 группа
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <numeric>

using namespace std;

class Rational {
private:
    int num, denom;
    void reduce() {
        int g = gcd(abs(num), abs(denom));
        num /= g;
        denom /= g;
        if (denom < 0) {
            num = -num;
            denom = -denom;
        }
    }

public:
    Rational(int numerator = 0, int denominator = 1) : num(numerator), denom(denominator) {
        if (denom == 0)
            throw runtime_error("Знаменатель не может быть 0!");
        reduce();
    }

    int getNumerator() const { return num; }
    int getDenominator() const { return denom; }

    Rational operator+(const Rational& other) const {
        return Rational(num * other.denom + other.num * denom, denom * other.denom);
    }

    Rational operator-(const Rational& other) const {
        return Rational(num * other.denom - other.num * denom, denom * other.denom);
    }

    Rational operator*(const Rational& other) const {
        return Rational(num * other.num, denom * other.denom);
    }

    Rational operator/(const Rational& other) const {
        if (other.num == 0) throw runtime_error("Деление на 0!");
        return Rational(num * other.denom, denom * other.num);
    }

    Rational& operator+=(const Rational& other) {
        num = num * other.denom + other.num * denom;
        denom *= other.denom;
        reduce();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        num = num * other.denom - other.num * denom;
        denom *= other.denom;
        reduce();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        num *= other.num;
        denom *= other.denom;
        reduce();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        if (other.num == 0) throw runtime_error("Деление на 0!");
        num *= other.denom;
        denom *= other.num;
        reduce();
        return *this;
    }

    bool operator==(const Rational& other) const {
        return num * other.denom == other.num * denom;
    }

    bool operator>(const Rational& other) const {
        return num * other.denom > other.num * denom;
    }

    bool operator<(const Rational& other) const {
        return num * other.denom < other.num * denom;
    }

    bool operator>=(const Rational& other) const {
        return !(*this < other);
    }

    bool operator<=(const Rational& other) const {
        return !(*this > other);
    }


    Rational operator-() const { return Rational(-num, denom); }

    friend std::ostream& operator<<(std::ostream& out, const Rational& r) {
        if (r.denom == 1)
            out << r.num;
        else
            out << r.num << "/" << r.denom;
        return out;
    }
};

Rational abs(const Rational& r) {
    return Rational(abs(r.getNumerator()), abs(r.getDenominator()));
}

template<size_t M, size_t N, typename Field = Rational>
class Matrix {
protected:
    vector<vector<Field>> m;
public:

    Matrix() : m(M, vector<Field>(N, Field(0))) {}

   Matrix(const vector<vector<Field>>& data) : m(data) {
       m = data;
   }

   bool operator==(const Matrix<M, N, Field>& other) const {
       if (M != other.m.size() || N != other.m[0].size()) return false;
       for (size_t i = 0; i < M; i++)
           for (size_t j = 0; j < N; j++)
               if (m[i][j] != other.m[i][j]) return false;
       return true;
   }

    bool operator !=(const Matrix& other) const {
        return !(*this == other);
    }

    Matrix& operator += (const Matrix& other) {
        if (M != other.m.size() || N != other.m[0].size())
            throw runtime_error("Размеры матриц не совпадают!");
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                this->m[i][j] += other.m[i][j];
        return *this;
    }

    Matrix& operator -= (const Matrix& other) {
        if (M != other.m.size() || N != other.m[0].size())
            throw runtime_error("Размеры матриц не совпадают!");
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                this->m[i][j] -= other.m[i][j];
        return *this;
    }

    Matrix operator + (const Matrix& other) const {
        Matrix temp = *this;
        temp += other;
        return temp;
    }

    Matrix operator - (const Matrix& other) const {
        Matrix temp = *this;
        temp -= other;
        return temp;
    }

    Matrix operator * (Field value) const {
        Matrix temp = *this;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                temp.m[i][j] = m[i][j] * value;
        return temp;
    }

    template<size_t P> 
    Matrix<M, P, Field> operator*(const Matrix<N, P, Field>& other) const {
        Matrix<M, P, Field> result;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < P; j++) {
                for (size_t k = 0; k < N; k++) {
                    result(i, j) += m[i][k] * other(k, j);
                }
            }
        }
        return result;
    }


    Matrix<N, M, Field> transposed() const {
        vector<vector<Field>> transposed_data(N, vector<Field>(M));
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                transposed_data[j][i] = this->m[i][j];

        return Matrix<N, M, Field>(transposed_data);
    }

    size_t rank() const {
        Matrix<M, N, Field> temp = *this;
        size_t rank = 0;

        for (size_t col = 0, row = 0; col < N && row < M; col++) {
            size_t pivot = row;
            for (size_t i = row + 1; i < M; i++) {
                if (abs(temp.m[i][col]) > abs(temp.m[pivot][col])) {
                    pivot = i;
                }
            }

            if (abs(temp.m[pivot][col]) == Field(0)) continue;

            swap(temp.m[pivot], temp.m[row]);
            rank++;

            for (size_t i = row + 1; i < M; i++) {
                Field factor = temp.m[i][col] / temp.m[row][col];
                for (size_t j = col; j < N; j++) {
                    temp.m[i][j] -= factor * temp.m[row][j];
                }
            }
            row++;
        }
        return rank;
    }

    const vector<Field>& getRow(size_t row) const {
        if (row >= M) throw out_of_range("Индекс строки выходит за границы!");
        return m[row];
    }

    vector<Field> getColumn(size_t col) const {
        if (col >= N) throw out_of_range("Индекс столбца выходит за границы!");
        vector<Field> column(M);
        for (size_t i = 0; i < M; i++)
            column[i] = m[i][col];
        return column;
    }
    
    Field& operator()(size_t i, size_t j) {
        if (i >= M || j >= N) throw out_of_range("Индекс выходит за границы!");
        return m[i][j];
    }

    const Field& operator()(size_t i, size_t j) const {
        if (i >= M || j >= N) throw out_of_range("Индекс выходит за границы!");
        return m[i][j];
    }

    vector<Field>& operator[](size_t i) {
        if (i >= M) throw out_of_range("Индекс выходит за границы!");
        return m[i];
    }

    const vector<Field>& operator[](size_t i) const {
        if (i >= M) throw out_of_range("Индекс выходит за границы!");
        return m[i];
    }

    friend istream& operator>>(istream& in, Matrix& mat) {
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                in >> mat.m[i][j];
        return in;
    }

    friend ostream& operator<<(ostream& out, const Matrix& mat) {
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++)
                out << mat.m[i][j] << " ";
            out << endl;
        }
        return out;
    }
};

template<size_t N, typename Field = Rational>
class SquareMatrix : public Matrix<N, N, Field> {
public:

   using Matrix<N, N, Field>::Matrix;

    SquareMatrix() : Matrix<N, N, Field> (){
        for (size_t i = 0; i < N; i++) {
            this->m[i][i] = Field(1);
        }
    }

    SquareMatrix& operator*=(const SquareMatrix& other) {
        if (N != other.m[0].size())  throw runtime_error("Размеры матриц не совпадают!");
        SquareMatrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp.m[i][j] = 0;
                for (size_t k = 0; k < N; k++) {
                    temp.m[i][j] += this->m[i][k] * other.m[k][j];
                }
            }
        }
        *this = temp;
        return *this;
    }

    Field det() const {
        SquareMatrix<N, Field> temp = *this;
        Field det = Field(1);

        for (size_t i = 0; i < N; i++) {
            size_t pivot = i;
            for (size_t j = i + 1; j < N; j++)
                if (abs(temp(j, i)) > abs(temp(pivot, i)))
                    pivot = j;

            if (temp(pivot, i) == Field(0))
                return Field(0);

            if (i != pivot) {
                swap(temp[i], temp[pivot]); 
                det *= Field(-1);
            }

            det *= temp(i, i);

            for (size_t j = i + 1; j < N; j++) {
                Field factor = temp(j, i) / temp(i, i);
                for (size_t k = i; k < N; k++)
                    temp(j, k) -= factor * temp(i, k);
            }
        }
        return det;
    }


    Field trace() const {
        Field tr = Field(0);
        for (size_t i = 0; i < N; i++)
            tr += this->m[i][i];
        return tr;
    }

    SquareMatrix inverted() const {
        SquareMatrix<N, Field> aug = *this;
        SquareMatrix<N, Field> inv;

        for (size_t i = 0; i < N; i++) {
            size_t pivot = i;
            for (size_t j = i + 1; j < N; j++)
                if (abs(aug.m[j][i]) > abs(aug.m[pivot][i]))
                    pivot = j;

            if (aug.m[pivot][i] == Field(0))
                throw runtime_error("Матрица вырождена и не имеет обратной!");

            swap(aug.m[i], aug.m[pivot]);
            swap(inv.m[i], inv.m[pivot]);

            Field diag = aug.m[i][i];
            for (size_t j = 0; j < N; j++) {
                aug.m[i][j] /= diag;
                inv.m[i][j] /= diag;
            }

            for (size_t j = 0; j < N; j++) {
                if (i != j) {
                    Field factor = aug.m[j][i];
                    for (size_t k = 0; k < N; k++) {
                        aug.m[j][k] -= factor * aug.m[i][k];
                        inv.m[j][k] -= factor * inv.m[i][k];
                    }
                }
            }
        }
        return inv;
    }

    void invert() {
        *this = this->inverted();
    }
};

int main() {
    setlocale(LC_ALL, ".1251");

    Matrix<1, 2, int> n;
    cout << "Исходная матрица A 1*2:" << endl << n << endl;

    SquareMatrix<3, int> n1;
    cout << "Исходная матрица A 3*3:" << endl << n1 << endl;

    Matrix<3, 4, int> A({ {1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 1} });
    cout << "Исходная матрица A 3*4:" << endl << A << endl;

    Matrix<3, 4, int> A1({ {1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 1} });
    cout << "Исходная матрица A 3*4:" << endl << A1 << endl;

    cout << "A += A1" << endl << (A += A1) << endl;
    cout << "A -= A1" << endl << (A -= A1) << endl;
    cout << "A + A1" << endl << (A + A1) << endl;
    cout << "A - A1" << endl << (A - A1) << endl;
    cout << "A == A1 : " << (A == A1) << endl;
    cout << "A != A1 : " << (A != A1) << endl << endl;

    Matrix<4, 3, int> C({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, { 1, 5, 4 } });
    cout << "Исходная матрица С 4*3:" << endl << C << endl;
    cout << "A * 3" << endl << (A * 3) << endl << endl;
    cout << "A * C" << endl << (A * C) << endl << endl;

    //cout << "Исходная матрица A 4*3:" << endl << A;
    //cout << "A == B : " << (A == C) << endl;
    // ошибка компиляции так как не совпадают размеры

    cout << "A trasposed: " << endl << A.transposed() << endl;
    cout << "A rank: " << A.rank() << endl;

    SquareMatrix<2> B({ {1, 2}, {4, 5} });
    cout << "Исходная матрица B 2*2:" << endl << B << endl;
    SquareMatrix<2> D({ {3, 4}, {6, 7} });
    cout << "Исходная матрица D 2*2:" << endl << D << endl;

    cout << "B *= C" << endl << (B *= D) << endl;
    cout << "B det : " << B.det() << endl;
    cout << "B trace : " << B.trace() << endl;
    cout << "B inverted" << endl << B.inverted() << endl << endl;
    B.invert();
    cout << "B invert" << endl << B << endl << endl;

    cout << "Покажем что возможно использовать для SquareMatrix методы из Matrix" << endl << endl;
    cout << "B.getRow(0)" << endl;
    vector<Rational> b = B.getRow(0);
    for (auto x : b) {
        cout << x << endl;
    }
    cout << "B.getColumn(0)" << endl;
    b = B.getColumn(0);
    for (auto x : b) {
        cout << x << endl;
    }
    cout << "B(1, 0) : " << B(1, 0) << endl;
    cout << "B[1][0] : " << B[1][0] << endl;

    //cout << A.inverted();
    //ошибка компиляции, так как А не квадратная матрица и для нее невозможно найти обратную

    return 0;
}