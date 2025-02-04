#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, ".1251");
    int A, B, C;
    cout << "Enter A, B, C" << endl;
    cin >> A >> B >> C;
    if (A == B && B == C) {
        cout << "All numbers are equal: " << A << endl;
        return 0;
    }
    int maxVal = max(A, max(B, C));
    cout << "Largest number: " << maxVal << endl;
    int minVal = min(A, min(B, C));
    cout << "Smallest number: " << minVal << endl;
    return 0;
}
