#pragma once
#include <vector>
#include <windows.h>

struct ThreadData {
    std::vector<int>* arr;
    int min_idx = 0;
    int max_idx = 0;
    double average = 0;
};

inline void find_min_max(const std::vector<int>& arr, int& min_idx, int& max_idx) {
    if (arr.empty()) return;
    min_idx = 0; max_idx = 0;
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[min_idx]) min_idx = (int)i;
        Sleep(7);
        if (arr[i] > arr[max_idx]) max_idx = (int)i;
        Sleep(7);
    }
}

inline double calculate_average(const std::vector<int>& arr) {
    if (arr.empty()) return 0;
    double sum = 0;
    for (int x : arr) {
        sum += x;
        Sleep(12);
    }
    return sum / arr.size();
}
