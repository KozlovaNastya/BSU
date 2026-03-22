#pragma once
#include <cmath>

inline double f1(double x) {
    return x * std::cosh(x);
}

inline double f1_double(double x) {
    return 2.0 * std::sinh(x) + x * std::cosh(x);
}

inline double f2(double x) {
    return std::abs(2.0 * x - 1.0);
}

inline double f2_double(double x) {
    return 0.0;
}
