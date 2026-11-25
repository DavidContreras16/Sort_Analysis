# Sort Analysis

Implementacion en C++ de seis algoritmos de ordenamiento. Cada algoritmo vive
en su propio header y recibe un `std::vector<int>`.

## Algoritmos

- Insertion Sort
- Selection Sort
- Bubble Sort
- Merge Sort
- Heap Sort
- Quick Sort

## Estructura

```text
Sort_Analysis/
├── CMakeLists.txt
├── include/sorts/
│   ├── insertion_sort.hpp
│   ├── selection_sort.hpp
│   ├── bubble_sort.hpp
│   ├── merge_sort.hpp
│   ├── heap_sort.hpp
│   └── quick_sort.hpp
├── scripts/
│   └── requirements.txt
├── data/
└── results/
```

## Uso

```cpp
#include "sorts/insertion_sort.hpp"

std::vector<int> data = {5, 2, 4, 1, 3};
insertion_sort(data);
```

## Compilacion

```powershell
cmake -S . -B build
cmake --build build
```

Las implementaciones son header-only. El programa de benchmark se agregara en
el siguiente paso.

## Analisis

Los resultados se guardaran en `data/` y la hoja de calculo con las graficas en
`results/`. Las dependencias de Python estan en `scripts/requirements.txt`.
