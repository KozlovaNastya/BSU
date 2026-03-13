#include <iostream>
#include <vector>
#include <windows.h>

struct ThreadData {
    std::vector<int>* arr;
    int min_idx;
    int max_idx;
    double average;
};

DWORD WINAPI min_max(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    auto& a = *(data->arr);

    data->min_idx = 0;
    data->max_idx = 0;

    for (size_t i = 1; i < a.size(); ++i) {
        if (a[i] < a[data->min_idx]) data->min_idx = i;
        Sleep(7);
        if (a[i] > a[data->max_idx]) data->max_idx = i;
        Sleep(7);
    }
    std::cout << "Min: " << a[data->min_idx] << ", Max: " << a[data->max_idx] << std::endl;
    return 0;
}

DWORD WINAPI average(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    auto& a = *(data->arr);
    double sum = 0;

    for (int x : a) {
        sum += x;
        Sleep(12);
    }
    data->average = sum / a.size();
    std::cout << "Average: " << data->average << std::endl;
    return 0;
}


int main() {
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& x : arr) std::cin >> x;

    ThreadData data = { &arr, 0, 0, 0.0 };

    HANDLE hMinMax = CreateThread(NULL, 0, min_max, &data, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average, &data, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    arr[data.min_idx] = (int)data.average;
    arr[data.max_idx] = (int)data.average;

    for (int x : arr) std::cout << x << " ";

    CloseHandle(hMinMax);
    CloseHandle(hAverage);
    return 0;
}
