#include <iostream>
#include <set>
#include <cmath>
using namespace std;
set<int> sieveOfEratosthenes(int N) {
    set<int> primes;
    for (int i = 2; i <= N; ++i)
        primes.insert(i);
    for (int i = 2; i <= std::sqrt(N); ++i) {
        if (primes.find(i) != primes.end()) {
            for (int j = i * i; j <= N; j += i)
                primes.erase(j);
        }
    }
    return primes;
}
int main() {
    int N;
    cout << "Enter number N: ";
    cin >> N;
    if (N < 2) {
        cout << "There is no prime numbers <= " << N << endl;
        return 0;
    }
    set<int> primes = sieveOfEratosthenes(N);
    cout << "Prime numbers <= " << N << ": ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    cout << endl;
    return 0;
}
