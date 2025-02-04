#include <iostream>
#include <set>
#include <cmath>
using namespace std;
// Функция для нахождения всех простых чисел <= N
set<int> sieveOfEratosthenes(int N) {
    set<int> primes;
    // Инициализация множества всех чисел от 2 до N
    for (int i = 2; i <= N; ++i)
        primes.insert(i);
    // Алгоритм "Решето Эратосфена"
    for (int i = 2; i <= std::sqrt(N); ++i) {
        if (primes.find(i) != primes.end()) { // Если i ещё в множестве
            // Удаляем все кратные i
            for (int j = i * i; j <= N; j += i)
                primes.erase(j);
        }
    }
    return primes;
}
int main() {
    int N;
    cout << "Введите число N: ";
    cin >> N;
    if (N < 2) {
        cout << "Нет простых чисел меньше или равных " << N << endl;
        return 0;
    }
    set<int> primes = sieveOfEratosthenes(N);
    cout << "Простые числа <= " << N << ": ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    cout << endl;
    return 0;
}
