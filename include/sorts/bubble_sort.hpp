#pragma once

#include <chrono>
#include <utility>
#include <vector>

void bubble_sort(std::vector<int>& data) {
    int n = static_cast<int>(data.size());

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

double ExecBubbleSort(std::vector<int>& data) {
    auto inicio = std::chrono::steady_clock::now();
    bubble_sort(data);
    auto fin = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duracion = fin - inicio;
    return duracion.count();
}