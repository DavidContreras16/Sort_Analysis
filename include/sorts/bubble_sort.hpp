#pragma once

#include <utility>
#include <vector>

inline void bubble_sort(std::vector<int>& data) {
    int n = static_cast<int>(data.size());

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}
