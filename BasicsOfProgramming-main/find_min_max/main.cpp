#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, ".1251");

    int A, B, C;
    cout << "Введите A, B, C" << endl;
    cin >> A >> B >> C;

    // Проверка на равенство всех чисел
    if (A == B && B == C) {
        cout << "Все числа равны: " << A << endl;
        return 0; // Завершаем программу, так как нет смысла искать максимум/минимум
    }

    // Поиск наибольшего числа
    int maxVal = max(A, max(B, C));
    cout << "Наибольшее число: " << maxVal << endl;

    // Поиск наименьшего числа
    int minVal = min(A, min(B, C));
    cout << "Наименьшее число: " << minVal << endl;

    return 0;
}
