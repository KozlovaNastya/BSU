#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

struct Point {
    double x, y;
};

// Алгоритм де Кастельжо для вычисления точки на кривой при параметре t [0, 1]
Point deCasteljau(std::vector<Point> points, double t) {
    int n = points.size();
    // Итеративно сокращаем количество точек до одной
    for (int j = 1; j < n; ++j) {
        for (int k = 0; k < n - j; ++k) {
            points[k].x = (1 - t) * points[k].x + t * points[k + 1].x;
            points[k].y = (1 - t) * points[k].y + t * points[k + 1].y;
        }
    }
    return points[0];
}

void printBezierPoints(const std::string& label, const std::vector<Point>& controlPoints) {
    std::cout << "--- " << label << " ---" << std::endl;
    std::cout << "Control Points: ";
    for (const auto& p : controlPoints) std::cout << "(" << p.x << ", " << p.y << ") ";
    std::cout << "\n\nCurve Points (t from 0 to 1):" << std::endl;

    // Генерируем 10 точек
    for (double t = 0; t <= 1.001; t += 0.1) {
        Point p = deCasteljau(controlPoints, t);
        std::cout << std::fixed << std::setprecision(3) << "t=" << t << " -> (" << p.x << ", " << p.y << ")" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    Point q0 = { -4, -2 };
    Point q5 = { 6, 6 };

    std::vector<std::vector<Point>> allDatasets = {
        {q0, {-2, 5}, {0, -5}, {2, 8}, {4, 0}, q5},     // Набор 1: Зигзаг
        {q0, {-3, 0}, {-1, 2}, {1, 4}, {3, 6}, q5},     // Набор 2: Почти прямая
        {q0, {2, -2}, {4, -2}, {-2, 6}, {0, 6}, q5},    // Набор 3: Петля
        {q0, {-5, 5}, {10, 5}, {-5, -5}, {10, -5}, q5}  // Набор 4: Сложная форма
    };

    for (int i = 0; i < 4; ++i) {
        printBezierPoints("Dataset " + std::to_string(i + 1), allDatasets[i]);
    }

    return 0;
}
