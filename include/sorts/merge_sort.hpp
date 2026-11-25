#pragma once

#include <vector>

inline void merge_parts(std::vector<int>& data, std::vector<int>& temp, int left, int mid,
                        int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (data[i] <= data[j]) {
            temp[k] = data[i];
            ++i;
        } else {
            temp[k] = data[j];
            ++j;
        }
        ++k;
    }

    while (i <= mid) {
        temp[k] = data[i];
        ++i;
        ++k;
    }

    while (j <= right) {
        temp[k] = data[j];
        ++j;
        ++k;
    }

    for (int index = left; index <= right; ++index) {
        data[index] = temp[index];
    }
}

inline void merge_sort_range(std::vector<int>& data, std::vector<int>& temp, int left,
                             int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    merge_sort_range(data, temp, left, mid);
    merge_sort_range(data, temp, mid + 1, right);
    merge_parts(data, temp, left, mid, right);
}

inline void merge_sort(std::vector<int>& data) {
    if (data.size() < 2) {
        return;
    }

    std::vector<int> temp(data.size());
    merge_sort_range(data, temp, 0, static_cast<int>(data.size()) - 1);
}
