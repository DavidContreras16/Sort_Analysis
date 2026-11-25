#pragma once

#include <chrono>
#include <utility>
#include <vector>

inline void sift_down(std::vector<int>& data, int root, int count) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < count && data[left] > data[largest]) {
            largest = left;
        }

        if (right < count && data[right] > data[largest]) {
            largest = right;
        }

        if (largest == root) {
            return;
        }

        std::swap(data[root], data[largest]);
        root = largest;
    }
}

inline void heap_sort(std::vector<int>& data) {
    int n = static_cast<int>(data.size());

    for (int i = n / 2 - 1; i >= 0; --i) {
        sift_down(data, i, n);
    }

    for (int i = n - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        sift_down(data, 0, i);
    }
}

double ExecHeapSort(std::vector<int>& data) {
    auto inicio = std::chrono::steady_clock::now();
    heap_sort(data);
    auto fin = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duracion = fin - inicio;
    return duracion.count();
}
