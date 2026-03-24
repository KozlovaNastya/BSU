#include <iostream>
#include "logic.h"

DWORD WINAPI min_max_thread(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    find_min_max(*(data->arr), data->min_idx, data->max_idx);
    return 0;
}

DWORD WINAPI average_thread(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    data->average = calculate_average(*(data->arr));
    return 0;
}

int main() {
    int n;
    std::cout << "Enter size: "; std::cin >> n;
    std::vector<int> arr(n);
    for (int& x : arr) std::cin >> x;

    ThreadData data; data.arr = &arr;

    HANDLE h1 = CreateThread(NULL, 0, min_max_thread, &data, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, average_thread, &data, 0, NULL);

    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);

    std::cout << "Min: " << arr[data.min_idx] << ", Max: " << arr[data.max_idx] << ", Avg: " << data.average << "\n";

    arr[data.min_idx] = (int)data.average;
    arr[data.max_idx] = (int)data.average;

    for (int x : arr) std::cout << x << " ";

    CloseHandle(h1); CloseHandle(h2);
    return 0;
}
