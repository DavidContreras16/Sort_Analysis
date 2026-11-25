#pragma once

#include <chrono>
#include <vector>

inline void insertion_sort(std::vector<int>& data) {
    int n = static_cast<int>(data.size());

    for (int i = 1; i < n; ++i) {
        int key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            --j;
        }

        data[j + 1] = key;
    }
}

double ExecInsertionSort(std::vector<int>& data) {
    auto inicio = std::chrono::steady_clock::now();
    insertion_sort(data);
    auto fin = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duracion = fin - inicio;
    return duracion.count();
}
