#pragma once

#include <chrono>
#include <utility>
#include <vector>

inline void selection_sort(std::vector<int>& data) {
    int n = static_cast<int>(data.size());

    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;

        for (int j = i + 1; j < n; ++j) {
            if (data[j] < data[min_index]) {
                min_index = j;
            }
        }

        std::swap(data[i], data[min_index]);
    }
}

double ExecSelectionSort(std::vector<int>& data) {
    auto inicio = std::chrono::steady_clock::now();
    selection_sort(data);
    auto fin = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duracion = fin - inicio;
    return duracion.count();
}
