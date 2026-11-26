# Datos del analisis

Este directorio contiene los resultados del benchmark y el contexto del equipo
en el que se midieron.

## Archivo de resultados

`resultados.csv` tiene una fila por algoritmo y tamano de arreglo:

| Columna | Descripcion |
|---|---|
| `Algoritmo` | Nombre del algoritmo ejecutado |
| `N` | Tamano del arreglo |
| `Tiempo_ms` | Tiempo de ejecucion en milisegundos |

El archivo se genera al ejecutar `.\build\sort_analysis.exe` y se usa como
entrada para `scripts/graficar.py`.

## Especificaciones del equipo

| Componente | Detalle |
|---|---|
| Equipo | HP Pavilion Gaming Laptop 15-ec1xxx |
| CPU | AMD Ryzen 5 4600H, 6 nucleos / 12 hilos, 3.0 GHz base (hasta 4.0 GHz de boost), 3 MB L2, 8 MB L3 |
| RAM | 24 GB instalados (23.36 GB utilizables): 16 GB TIMETEC + 8 GB Samsung a 3200 MHz |
| Sistema operativo | Windows 10 Home Single Language 22H2, 64 bits, build 19045 |
| Energia | Equipo conectado a corriente, plan de energia Equilibrado, bateria al 87% |
| Compilador | MinGW-W64 GCC 14.2.0, C++17 |
| Build | CMake 3.31.5 + Ninja 1.12.1, Release, `-O3 -DNDEBUG` |
| Python | 3.12.3, pandas 3.0.1, matplotlib 3.9.2 |

## Metodologia

- Los algoritmos se ejecutan en un solo hilo.
- La entrada se genera con `std::mt19937` sembrado con `std::random_device`, con
  enteros uniformes entre 1 y 10,000,000.
- Para cada `N` se genera un arreglo base y cada algoritmo recibe una copia
  nueva, de modo que todos ordenan exactamente la misma entrada.
- El tiempo se mide con `std::chrono::steady_clock` y se reporta en
  milisegundos. El cronometro cubre solo la llamada al algoritmo; la generacion
  del arreglo y la copia quedan fuera.
- Se hace una sola repeticion por algoritmo y tamano; no se promedian varias
  corridas.
- `N = 1,000` y `N = 50,000` se miden con los seis algoritmos. Para
  `N = 1,000,000`, `10,000,000` y `100,000,000` solo se miden Merge, Heap y
  Quick Sort.
- Con `N = 100,000,000` cada arreglo ocupa 400 MB y el pico de memoria es de
  aproximadamente 1.2 GB, por lo que los datos caben en RAM y no hay swap.

## Por que faltan los algoritmos O(n^2) en los tamanos grandes

Pasar de 50,000 a 100,000,000 es 2000 veces mas datos. En un algoritmo O(n^2)
el tiempo crece con el cuadrado, es decir, 4,000,000 veces. Con los tiempos
medidos a 50,000:

| Algoritmo | 50,000 (medido) | 1,000,000 (estimado) | 10,000,000 (estimado) | 100,000,000 (estimado) |
|---|---:|---:|---:|---:|
| Bubble Sort | 7.16 s | ~48 min | ~3.3 dias | ~332 dias |
| Insertion Sort | 0.314 s | ~2.1 min | ~3.5 horas | ~14.5 dias |
| Selection Sort | 0.896 s | ~6.0 min | ~10.0 horas | ~41.5 dias |

Las estimaciones usan el tiempo medido a 50,000 y crecimiento cuadratico. En la
practica pueden ser peores porque a partir de 10M el arreglo ya no cabe en
cache. Por eso el benchmark no ejecuta esos algoritmos en los tamanos grandes:
el programa tardaria dias o meses en terminar.

Los tres algoritmos O(n log n) si se midieron hasta 100M. En la ultima ejecucion
registrada:

| Algoritmo | 100,000,000 |
|---|---:|
| Merge Sort | 13.62 s |
| Heap Sort | 49.17 s |
| Quick Sort | 9.11 s |

Heap Sort es mas lento que Merge y Quick por su patron de acceso a memoria:
`sift_down` salta por todo el arreglo y genera muchos fallos de cache.

## Graficas

El script `scripts/graficar.py` lee `resultados.csv` y genera:

| Archivo | Contenido |
|---|---|
| `results/tiempo_vs_n.png` | Tiempo vs `N` para todos los algoritmos, en escala log-log |
| `results/comparacion_por_n.png` | Comparacion de algoritmos para cada tamano de arreglo |
| `results/crecimiento_por_complejidad.png` | Crecimiento de los O(n^2) frente a los O(n log n) |

Para regenerarlas:

```powershell
pip install -r scripts/requirements.txt
python scripts/graficar.py
```

El script detecta automaticamente si el CSV usa coma o punto y coma como
separador.

## Como regenerar los datos

```powershell
cmake -S . -B build
cmake --build build
.\build\sort_analysis.exe
python scripts\graficar.py
```

Los tiempos pueden variar entre ejecuciones por la temperatura del CPU, los
procesos en segundo plano y el plan de energia. Para comparar corridas conviene
usar el mismo equipo, el mismo plan de energia y la misma configuracion.
