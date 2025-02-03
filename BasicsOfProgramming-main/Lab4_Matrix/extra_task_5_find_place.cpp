#include <iostream>
using namespace std;
int main() {
    int n, m, k, count = 0, row = 0, maxCount = 0;
    cin >> n >> m;
    int matrix[100][100];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> matrix[i][j];
    cin >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0)
                count++;
            if (matrix[i][j] == 1) {
                if (count > maxCount)
                    maxCount = count;
                count = 0;
                }
            }
            if (maxCount >= k) {
                row = i + 1;
                break;
            }
            count = 0;
            maxCount = 0;
        }
        cout << row;
        return 0;
    }