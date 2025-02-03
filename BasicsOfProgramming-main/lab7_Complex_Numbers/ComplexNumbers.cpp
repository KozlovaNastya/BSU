#include <iostream>
using namespace std;

class ComplexNumbers {
private:
    double real;  // Действительная часть
    double img;  // Мнимая часть

public:
    // Конструктор по умолчанию
    ComplexNumbers(double r = 0, double i = 0) : real(r), img(i) {}

    // Геттеры и сеттеры
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

    // Перегрузка операторов
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

    // Проверка деления на 0
    ComplexNumbers operator/(const ComplexNumbers& other) const {
        if (other.real == 0 && other.img == 0) {
            cout << "Ошибка: деление на 0!" << endl;
            return ComplexNumbers();  // Возвращаем нулевое комплексное число
        }
        double denominator = other.real * other.real + other.img * other.img;
        return ComplexNumbers((real * other.real + img * other.img) / denominator,
            (img * other.real - real * other.img) / denominator);
    }

    // Функция для вывода комплексного числа
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
    cout << "Введите действительную и мнимую часть первого комплексного числа:" << endl;
    cin >> real1 >> img1;
    cout << "Введите действительную и мнимую часть второго комплексного числа:" << endl;
    cin >> real2 >> img2;
    cout << "Введите знак операции:" << endl;
    cin >> operation;

    ComplexNumbers num1(real1, img1);
    ComplexNumbers num2(real2, img2);
    ComplexNumbers result;

    switch (operation)
    {
    case '+':
        result = num1 + num2;
        cout << "Сумма:" << endl;
        result.print();
        break;
    case '-':
        result = num1 - num2;
        cout << "Разность:" << endl;
        result.print();
        break;
    case '*':
        result = num1 * num2;
        cout << "Произведение:" << endl;
        result.print();
        break;
    case '/':
        result = num1 / num2;
        cout << "Частное:" << endl;
        result.print();
        break;
    default:
        cout << "Неизвестный знак операции" << endl;
        break;
    }
    return 0;
}
