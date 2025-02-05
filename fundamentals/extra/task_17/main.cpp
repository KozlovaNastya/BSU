#include <iostream>
#include <ctime>;
using namespace std;
int main() {
	int n, k;
	cin >> n >> k;
	const int N_max = 20;
	int A[N_max][N_max];
	int B[N_max][N_max];
	int C[N_max][N_max];
	srand(0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			A[i][j] = rand() % 100;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			B[i][j] = rand() % 100;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << B[i][j] << " ";
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			//C[i][j] = 0;
				for (int l = 0; l < n; l++)
					C[i][j] = A[i][l] * B[l][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << C[i][j] << " ";
		cout << endl;
	}
	return 0;
}
