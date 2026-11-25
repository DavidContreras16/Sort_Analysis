#pragma once

#include <utility>
#include <vector>

inline int partition_range(std::vector<int>& data, int low, int high) {
    int mid = low + (high - low) / 2;
    std::swap(data[mid], data[high]);

    int pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (data[j] < pivot) {
            ++i;
            std::swap(data[i], data[j]);
        }
    }

    std::swap(data[i + 1], data[high]);
    return i + 1;
}

inline void quick_sort_range(std::vector<int>& data, int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = partition_range(data, low, high);
    quick_sort_range(data, low, pivot - 1);
    quick_sort_range(data, pivot + 1, high);
}

inline void quick_sort(std::vector<int>& data) {
    if (data.size() < 2) {
        return;
    }

    quick_sort_range(data, 0, static_cast<int>(data.size()) - 1);
}
