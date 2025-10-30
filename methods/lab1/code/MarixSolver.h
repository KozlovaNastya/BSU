#ifndef SEQUENCE_MANAGER_H 
#define SEQUENCE_MANAGER_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

class MatrixSolver {
private:
    int N;
    vector<vector<double>> A;
    vector<double> b;

public:
    MatrixSolver(int n);

    void initializeMatrix();
    void printMatrix(const vector<vector<double>>& mat, const string& name);
    void printVector(const vector<double>& vec, const string& name);
    double residualNorm(const vector<double>& x);
    double frobeniusNorm(const vector<vector<double>>& mat);
    vector<double> gaussWithPivot(double& determinant);
    vector<double> rotationMethod(vector<vector<double>>& Q, vector<vector<double>>& R);
    double checkQRDecomposition(const vector<vector<double>>& Q,
        const vector<vector<double>>& R);
};

#endif