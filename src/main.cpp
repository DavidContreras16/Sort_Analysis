#include <filesystem>
#include <fstream>
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

struct Resultado {
    std::string algoritmo;
    int n;
    double tiempo;
};

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

void exportToCSV(const std::string& filename, const std::vector<Resultado>& resultados) {
    const std::filesystem::path ruta(filename);
    if (ruta.has_parent_path()) {
        std::filesystem::create_directories(ruta.parent_path());
    }

    std::ofstream archivo(ruta);
    if (!archivo) {
        std::cerr << "No se pudo abrir " << ruta.string() << '\n';
        return;
    }

    archivo << "Algoritmo,N,Tiempo_ms\n";
    for (const Resultado& resultado : resultados) {
        archivo << resultado.algoritmo << ',' << resultado.n << ',' << std::fixed
                << std::setprecision(6) << resultado.tiempo << '\n';
    }
}

void Sortear(const std::string& nombre, const std::vector<int>& original,
             double (*exec)(std::vector<int>&), std::vector<Resultado>& resultados) {
    std::vector<int> copia = original;

    const double tiempo = exec(copia);
    std::cout << std::left << std::setw(16) << nombre << " N = " << original.size()
              << "  T = " << std::fixed << std::setprecision(6) << tiempo << " ms\n";

    resultados.push_back({nombre, static_cast<int>(original.size()), tiempo});
}

int main() {

    std::vector<int> arr_1 = generateArray(1000);
    std::vector<int> arr_2 = generateArray(50000);
    std::vector<int> arr_3 = generateArray(1000000);
    std::vector<int> arr_4 = generateArray(10000000);
    std::vector<int> arr_5 = generateArray(100000000);

    std::vector<Resultado> resultados;

    std::cout << "\nN = " << arr_1.size() << '\n';
    Sortear("Bubble Sort", arr_1, ExecBubbleSort, resultados);
    Sortear("Insertion Sort", arr_1, ExecInsertionSort, resultados);
    Sortear("Selection Sort", arr_1, ExecSelectionSort, resultados);
    Sortear("Merge Sort", arr_1, ExecMergeSort, resultados);
    Sortear("Heap Sort", arr_1, ExecHeapSort, resultados);
    Sortear("Quick Sort", arr_1, ExecQuickSort, resultados);

    std::cout << "\nN = " << arr_2.size() << '\n';
    Sortear("Bubble Sort", arr_2, ExecBubbleSort, resultados);
    Sortear("Insertion Sort", arr_2, ExecInsertionSort, resultados);
    Sortear("Selection Sort", arr_2, ExecSelectionSort, resultados);
    Sortear("Merge Sort", arr_2, ExecMergeSort, resultados);
    Sortear("Heap Sort", arr_2, ExecHeapSort, resultados);
    Sortear("Quick Sort", arr_2, ExecQuickSort, resultados);

    std::cout << "\nN = " << arr_3.size() << '\n';
    Sortear("Bubble Sort", arr_3, ExecBubbleSort, resultados);
    Sortear("Insertion Sort", arr_3, ExecInsertionSort, resultados);
    Sortear("Selection Sort", arr_3, ExecSelectionSort, resultados);
    Sortear("Merge Sort", arr_3, ExecMergeSort, resultados);
    Sortear("Heap Sort", arr_3, ExecHeapSort, resultados);
    Sortear("Quick Sort", arr_3, ExecQuickSort, resultados);

    std::cout << "\nN = " << arr_4.size() << '\n';
    Sortear("Merge Sort", arr_4, ExecMergeSort, resultados);
    Sortear("Heap Sort", arr_4, ExecHeapSort, resultados);
    Sortear("Quick Sort", arr_4, ExecQuickSort, resultados);

    std::cout << "\nN = " << arr_5.size() << '\n';
    Sortear("Merge Sort", arr_5, ExecMergeSort, resultados);
    Sortear("Heap Sort", arr_5, ExecHeapSort, resultados);
    Sortear("Quick Sort", arr_5, ExecQuickSort, resultados);

    const std::string archivo = "data/resultados.csv";
    exportToCSV(archivo, resultados);
    std::cout << "\nResultados exportados a " << archivo << '\n';

    return 0;
}
