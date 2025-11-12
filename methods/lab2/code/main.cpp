#include <iostream>
#include <iomanip>
#include "iterative.h"

int main() {
    const int n = 15;
    const int studentNumber = 6;
    const double epsilon = 1e-5;

    std::cout << "Matrix size: " << n << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    IterativeMethods solver(n, studentNumber);

    std::cout << "PRIOR ESTIMATION:" << std::endl;
    int prior_iterations = solver.calculatePriorIterations(epsilon);
    std::cout << "Estimated iterations (prior): " << prior_iterations << std::endl;
    std::cout << "Matrix B norm: " << solver.getBNorm() << std::endl;

    std::cout << "\n1. SIMPLE ITERATION METHOD:" << std::endl;
    int iterations;
    auto solution1 = solver.simpleIteration(epsilon, iterations);
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Obtained solution: ";
    solver.printVector(solution1);
    std::cout << "Error norm: " << solver.calculateError(solution1) << std::endl;

    auto x_prev = solver.getLastXPrev();
    auto x_curr = solver.getLastXCurr();
    std::cout << "Posterior error estimate: " << solver.calculatePosteriorError(x_prev, x_curr) << std::endl;

    std::cout << "\n2. SEIDEL METHOD:" << std::endl;
    auto solution2 = solver.seidelMethod(iterations);
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Obtained solution: ";
    solver.printVector(solution2);
    std::cout << "Error norm: " << solver.calculateError(solution2) << std::endl;

    std::cout << "\n3. RELAXATION METHOD (ω = 0.5):" << std::endl;
    auto solution3 = solver.relaxationMethod(0.5, iterations + 23);
    std::cout << "Number of iterations: " << iterations + 23 << std::endl;
    std::cout << "Obtained solution: ";
    solver.printVector(solution3);
    std::cout << "Error norm: " << solver.calculateError(solution3) << std::endl;

    std::cout << "\n4. RELAXATION METHOD (ω = 1.5):" << std::endl;
    auto solution4 = solver.relaxationMethod(1.5, iterations);
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Obtained solution: ";
    solver.printVector(solution4);
    std::cout << "Error norm: " << solver.calculateError(solution4) << std::endl;

    std::cout << "\n5. EXACT SOLUTION:" << std::endl;
    auto exact = solver.getExactSolution();
    std::cout << "Exact solution: ";
    solver.printVector(exact);

    std::cout << "\n6. METHODS COMPARISON:" << std::endl;
    std::cout << "Simple iteration method: " << solver.calculateError(solution1) << std::endl;
    std::cout << "Seidel method: " << solver.calculateError(solution2) << std::endl;
    std::cout << "Relaxation method (ω=0.5): " << solver.calculateError(solution3) << std::endl;
    std::cout << "Relaxation method (ω=1.5): " << solver.calculateError(solution4) << std::endl;

    return 0;
}