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
├── src/
│   └── main.cpp
├── scripts/
│   ├── graficar.py
│   └── requirements.txt
├── data/
│   ├── README.md
│   └── resultados.csv
└── results/
    ├── README.md
    ├── tiempo_vs_n.png
    ├── comparacion_por_n.png
    └── crecimiento_por_complejidad.png
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

Las implementaciones son header-only.

## Benchmark

```powershell
.\build\sort_analysis.exe
```

El programa genera arreglos aleatorios con `N = 10,000`, `500,000`,
`1,000,000`, `10,000,000` y `100,000,000`, y muestra el tiempo de ejecucion de
cada algoritmo en milisegundos.

Cada algoritmo recibe una copia del mismo arreglo original. Los algoritmos
O(n^2) se ejecutan hasta `N = 1,000,000`; para `N = 10,000,000` y
`N = 100,000,000` solo se miden Merge Sort, Heap Sort y Quick Sort.

Al finalizar, los resultados se guardan en `data/resultados.csv` con las
columnas `Algoritmo`, `N` y `Tiempo_ms`. El archivo se puede abrir con Excel o
con cualquier editor de hojas de calculo.

Ejemplo de salida:

```text
N = 1000
Bubble Sort      N = 1000  T = 2.368700 ms
Insertion Sort   N = 1000  T = 0.172100 ms
Selection Sort   N = 1000  T = 0.498900 ms
Merge Sort       N = 1000  T = 0.092500 ms
Heap Sort        N = 1000  T = 0.084000 ms
Quick Sort       N = 1000  T = 0.063200 ms
```

## Analisis

```powershell
python scripts/graficar.py
```

El script lee `data/resultados.csv` y genera las graficas en `results/`. Las
especificaciones del equipo y la metodologia de medicion estan documentadas en
`data/README.md`; las graficas se muestran en `results/README.md`.
