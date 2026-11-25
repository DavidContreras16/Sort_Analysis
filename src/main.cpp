#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "sorts/bubble_sort.hpp"
#include "sorts/heap_sort.hpp"
#include "sorts/insertion_sort.hpp"
#include "sorts/merge_sort.hpp"
#include "sorts/quick_sort.hpp"
#include "sorts/selection_sort.hpp"

static std::mt19937 gen(std::random_device{}());

int randomInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

std::vector<int> generateArray(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = randomInt(1, 10000000);
    }

    return arr;
}

// Ejecuta el sort sobre una copia para que todos los algoritmos reciban el mismo arreglo.
void ejecutarYMostrar(const std::string& nombre, const std::vector<int>& original,
                      double (*exec)(std::vector<int>&)) {
    std::vector<int> copia = original;

    const double tiempo = exec(copia);
    std::cout << std::left << std::setw(16) << nombre << " N = " << original.size()
              << "  T = " << std::fixed << std::setprecision(6) << tiempo << " ms\n";
}

int main() {
    std::cout << "Generando arreglos...\n";

    std::vector<int> arr_1 = generateArray(1000);
    std::vector<int> arr_2 = generateArray(50000);
    std::vector<int> arr_3 = generateArray(1000000);
    std::vector<int> arr_4 = generateArray(10000000);
    std::vector<int> arr_5 = generateArray(100000000);

    std::cout << "\nN = " << arr_1.size() << '\n';
    ejecutarYMostrar("Bubble Sort", arr_1, ExecBubbleSort);
    ejecutarYMostrar("Insertion Sort", arr_1, ExecInsertionSort);
    ejecutarYMostrar("Selection Sort", arr_1, ExecSelectionSort);
    ejecutarYMostrar("Merge Sort", arr_1, ExecMergeSort);
    ejecutarYMostrar("Heap Sort", arr_1, ExecHeapSort);
    ejecutarYMostrar("Quick Sort", arr_1, ExecQuickSort);

    std::cout << "\nN = " << arr_2.size() << '\n';
    ejecutarYMostrar("Bubble Sort", arr_2, ExecBubbleSort);
    ejecutarYMostrar("Insertion Sort", arr_2, ExecInsertionSort);
    ejecutarYMostrar("Selection Sort", arr_2, ExecSelectionSort);
    ejecutarYMostrar("Merge Sort", arr_2, ExecMergeSort);
    ejecutarYMostrar("Heap Sort", arr_2, ExecHeapSort);
    ejecutarYMostrar("Quick Sort", arr_2, ExecQuickSort);

    // Los algoritmos O(n^2) solo se miden hasta N = 50,000.
    // Para los tamanos grandes se ejecutan Merge, Heap y Quick Sort.
    std::cout << "\nN = " << arr_3.size() << '\n';
    ejecutarYMostrar("Merge Sort", arr_3, ExecMergeSort);
    ejecutarYMostrar("Heap Sort", arr_3, ExecHeapSort);
    ejecutarYMostrar("Quick Sort", arr_3, ExecQuickSort);

    std::cout << "\nN = " << arr_4.size() << '\n';
    ejecutarYMostrar("Merge Sort", arr_4, ExecMergeSort);
    ejecutarYMostrar("Heap Sort", arr_4, ExecHeapSort);
    ejecutarYMostrar("Quick Sort", arr_4, ExecQuickSort);

    std::cout << "\nN = " << arr_5.size() << '\n';
    ejecutarYMostrar("Merge Sort", arr_5, ExecMergeSort);
    ejecutarYMostrar("Heap Sort", arr_5, ExecHeapSort);
    ejecutarYMostrar("Quick Sort", arr_5, ExecQuickSort);

    return 0;
}
