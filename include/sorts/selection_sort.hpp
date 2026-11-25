#pragma once

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
