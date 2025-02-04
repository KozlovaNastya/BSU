#include <iostream>
using namespace std;

class ComplexNumbers {
private:
    double real;
    double img;

public:
    ComplexNumbers(double r = 0, double i = 0) : real(r), img(i) {}

    double getReal() const { 
        return real; 
    }
    double getImg() const { 
        return img; 
    }
    void setReal(double r) { 
        real = r; 
    }
    void setImg(double i) { 
        img = i; 
    }

    ComplexNumbers operator+(const ComplexNumbers& other) const {
        return ComplexNumbers(real + other.real, img + other.img);
    }

    ComplexNumbers operator-(const ComplexNumbers& other) const {
        return ComplexNumbers(real - other.real, img - other.img);
    }

    ComplexNumbers operator*(const ComplexNumbers& other) const {
        return ComplexNumbers(real * other.real - img * other.img,
            real * other.img + img * other.real);
    }

    ComplexNumbers operator/(const ComplexNumbers& other) const {
        if (other.real == 0 && other.img == 0) {
            cout << "Error: division by 0!" << endl;
            return ComplexNumbers(); 
        }
        double denominator = other.real * other.real + other.img * other.img;
        return ComplexNumbers((real * other.real + img * other.img) / denominator,
            (img * other.real - real * other.img) / denominator);
    }

    void print() const {
        if (img >= 0)
            cout << real << "+" << img << "i" << endl;
        else
            cout << real << img << "i" << endl;
    }
};

int main() {
    setlocale(LC_ALL, ".1251");
    double real1, img1, real2, img2;
    char operation;
    cout << "Enter the real and imaginary part of the first complex number:" << endl;
    cin >> real1 >> img1;
    cout << "Enter the real and imaginary part of the second complex number:" << endl;
    cin >> real2 >> img2;
    cout << "Enter the operation sign:" << endl;
    cin >> operation;

    ComplexNumbers num1(real1, img1);
    ComplexNumbers num2(real2, img2);
    ComplexNumbers result;

    switch (operation)
    {
    case '+':
        result = num1 + num2;
        cout << "Add:" << endl;
        result.print();
        break;
    case '-':
        result = num1 - num2;
        cout << "Subtract:" << endl;
        result.print();
        break;
    case '*':
        result = num1 * num2;
        cout << "Multiply:" << endl;
        result.print();
        break;
    case '/':
        result = num1 / num2;
        cout << "Divide:" << endl;
        result.print();
        break;
    default:
        cout << "Unknown operation sign" << endl;
        break;
    }
    return 0;
}
