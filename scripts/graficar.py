from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import pandas as pd

BASE_DIR = Path(__file__).resolve().parent.parent
CSV_PATH = BASE_DIR / "data" / "resultados.csv"
RESULTS_DIR = BASE_DIR / "results"

ALGORITMOS = [
    "Bubble Sort",
    "Insertion Sort",
    "Selection Sort",
    "Merge Sort",
    "Heap Sort",
    "Quick Sort",
]

COLORES = {
    "Bubble Sort": "#d62728",
    "Insertion Sort": "#ff7f0e",
    "Selection Sort": "#bcbd22",
    "Merge Sort": "#2ca02c",
    "Heap Sort": "#9467bd",
    "Quick Sort": "#1f77b4",
}


def configurar_estilo():
    plt.rcParams.update(
        {
            "figure.facecolor": "white",
            "axes.facecolor": "white",
            "axes.edgecolor": "#b0b0b0",
            "axes.grid": True,
            "axes.axisbelow": True,
            "grid.color": "#d9d9d9",
            "grid.linestyle": "--",
            "grid.linewidth": 0.7,
            "font.size": 10,
            "axes.titlesize": 12,
            "axes.titleweight": "bold",
            "axes.labelsize": 10,
            "legend.fontsize": 9,
            "legend.frameon": False,
        }
    )


def cargar_resultados(ruta):
    if not ruta.exists():
        raise SystemExit(
            f"No se encontro {ruta}.\n"
            "Ejecuta primero el benchmark: .\\build\\sort_analysis.exe"
        )

    df = pd.read_csv(ruta, sep=None, engine="python")
    df.columns = [columna.strip() for columna in df.columns]

    requeridas = {"Algoritmo", "N", "Tiempo_ms"}
    faltantes = requeridas - set(df.columns)
    if faltantes:
        raise SystemExit(f"Faltan columnas en {ruta}: {', '.join(sorted(faltantes))}")

    df["Algoritmo"] = df["Algoritmo"].astype(str).str.strip()
    df["N"] = df["N"].astype(int)
    df["Tiempo_ms"] = df["Tiempo_ms"].astype(float)
    df = df.dropna(subset=["Algoritmo", "N", "Tiempo_ms"])

    if df.empty:
        raise SystemExit("El CSV no tiene filas de datos.")
    if (df["Tiempo_ms"] <= 0).any():
        raise SystemExit("Hay tiempos menores o iguales a cero; no se puede usar escala log.")

    duplicados = df.duplicated(subset=["Algoritmo", "N"]).sum()
    if duplicados:
        print(f"Advertencia: {duplicados} filas duplicadas; se conserva el ultimo valor.")
        df = df.drop_duplicates(subset=["Algoritmo", "N"], keep="last")

    orden = {nombre: indice for indice, nombre in enumerate(ALGORITMOS)}
    df["_orden"] = df["Algoritmo"].map(orden).fillna(len(ALGORITMOS))
    df = df.sort_values(["N", "_orden", "Algoritmo"]).drop(columns="_orden")
    return df.reset_index(drop=True)


def algoritmos_presentes(df):
    presentes = set(df["Algoritmo"])
    conocidos = [algoritmo for algoritmo in ALGORITMOS if algoritmo in presentes]
    desconocidos = sorted(presentes - set(ALGORITMOS))
    return conocidos + desconocidos


def formatear_n(n):
    if n >= 1_000_000:
        return f"{n // 1_000_000}M"
    if n >= 1_000:
        return f"{n // 1_000}k"
    return str(n)


def formatear_tiempo(milisegundos):
    if milisegundos >= 1_000:
        return f"{milisegundos / 1_000:.2f} s"
    if milisegundos >= 1:
        return f"{milisegundos:.2f} ms"
    return f"{milisegundos:.3f} ms"


def color_de(algoritmo):
    return COLORES.get(algoritmo, "#7f7f7f")


def graficar_tiempo_vs_n(df, ruta_salida):
    fig, ax = plt.subplots(figsize=(12, 7))

    for algoritmo in algoritmos_presentes(df):
        datos = df[df["Algoritmo"] == algoritmo].sort_values("N")
        ax.plot(
            datos["N"],
            datos["Tiempo_ms"],
            marker="o",
            markersize=6,
            linewidth=2,
            color=color_de(algoritmo),
            label=algoritmo,
        )

    ns = sorted(df["N"].unique())
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_xticks(ns)
    ax.set_xticklabels([formatear_n(n) for n in ns])
    ax.set_xlabel("Tamano del arreglo (N)")
    ax.set_ylabel("Tiempo de ejecucion (ms, escala log)")
    ax.set_title("Tiempo de ejecucion vs tamano del arreglo")
    ax.grid(True, which="major")
    ax.grid(True, which="minor", alpha=0.3)
    ax.legend(title="Algoritmo", ncol=2, loc="upper left")

    fig.tight_layout()
    fig.savefig(ruta_salida, dpi=170, bbox_inches="tight")
    plt.close(fig)


def graficar_comparacion_por_n(df, ruta_salida):
    ns = sorted(df["N"].unique())
    columnas = 3
    filas = (len(ns) + columnas - 1) // columnas
    fig, axes = plt.subplots(filas, columnas, figsize=(16, 4.5 * filas))
    axes = axes.flatten()

    for ax, n in zip(axes, ns):
        datos = df[df["N"] == n].sort_values("Tiempo_ms", ascending=False)
        posiciones = list(range(len(datos)))
        colores = [color_de(algoritmo) for algoritmo in datos["Algoritmo"]]
        minimo = datos["Tiempo_ms"].min()
        maximo = datos["Tiempo_ms"].max()

        ax.hlines(
            posiciones,
            xmin=minimo * 0.55,
            xmax=datos["Tiempo_ms"].to_numpy(),
            color=colores,
            linewidth=6,
            alpha=0.85,
        )
        ax.scatter(
            datos["Tiempo_ms"],
            posiciones,
            color=colores,
            s=55,
            zorder=3,
            edgecolors="white",
            linewidths=0.8,
        )

        ax.set_yticks(posiciones)
        ax.set_yticklabels(datos["Algoritmo"])
        ax.set_xscale("log")
        ax.set_xlim(minimo * 0.4, maximo * 3.2)
        ax.set_title(f"N = {n:,}")
        ax.set_xlabel("Tiempo (ms, escala log)")
        ax.grid(True, axis="x", which="major")
        ax.grid(True, axis="x", which="minor", alpha=0.3)
        ax.tick_params(axis="y", length=0)

        for posicion, valor in zip(posiciones, datos["Tiempo_ms"]):
            ax.text(
                valor * 1.15,
                posicion,
                formatear_tiempo(valor),
                va="center",
                fontsize=8.5,
            )

    for ax in axes[len(ns) :]:
        ax.axis("off")

    fig.suptitle("Comparacion de tiempos por tamano de arreglo", fontsize=16, fontweight="bold")
    fig.tight_layout(rect=[0, 0, 1, 0.94])
    fig.savefig(ruta_salida, dpi=170, bbox_inches="tight")
    plt.close(fig)


def graficar_crecimiento(df, ruta_salida):
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6.5), sharex=True)
    grupos = [
        (ax1, ["Bubble Sort", "Insertion Sort", "Selection Sort"], "Algoritmos O(n^2)"),
        (ax2, ["Merge Sort", "Heap Sort", "Quick Sort"], "Algoritmos O(n log n)"),
    ]
    ns = sorted(df["N"].unique())

    for ax, algoritmos, titulo in grupos:
        for algoritmo in algoritmos:
            datos = df[df["Algoritmo"] == algoritmo].sort_values("N")
            if datos.empty:
                continue
            ax.plot(
                datos["N"],
                datos["Tiempo_ms"],
                marker="o",
                linewidth=2,
                color=color_de(algoritmo),
                label=algoritmo,
            )

        ax.set_xscale("log")
        ax.set_yscale("log")
        ax.set_xticks(ns)
        ax.set_xticklabels([formatear_n(n) for n in ns])
        ax.set_title(titulo)
        ax.set_xlabel("Tamano del arreglo (N)")
        ax.set_ylabel("Tiempo de ejecucion (ms, escala log)")
        ax.grid(True, which="major")
        ax.grid(True, which="minor", alpha=0.3)
        ax.legend()

    ax1.text(
        0.98,
        0.05,
        "Solo medido hasta N = 50,000",
        transform=ax1.transAxes,
        ha="right",
        va="bottom",
        fontsize=9,
        color="#666666",
    )

    fig.suptitle(
        "Crecimiento de los tiempos: O(n^2) vs O(n log n)",
        fontsize=16,
        fontweight="bold",
    )
    fig.tight_layout(rect=[0, 0, 1, 0.94])
    fig.savefig(ruta_salida, dpi=170, bbox_inches="tight")
    plt.close(fig)


def main():
    configurar_estilo()
    RESULTS_DIR.mkdir(parents=True, exist_ok=True)
    df = cargar_resultados(CSV_PATH)

    print(f"Leyendo {CSV_PATH} ({len(df)} filas)")

    graficos = [
        ("tiempo_vs_n.png", graficar_tiempo_vs_n),
        ("comparacion_por_n.png", graficar_comparacion_por_n),
        ("crecimiento_por_complejidad.png", graficar_crecimiento),
    ]

    for nombre, funcion in graficos:
        ruta = RESULTS_DIR / nombre
        funcion(df, ruta)
        print(f"Generado: {ruta}")

    resumen = df.pivot(index="Algoritmo", columns="N", values="Tiempo_ms")
    resumen = resumen.reindex(
        [algoritmo for algoritmo in algoritmos_presentes(df) if algoritmo in resumen.index]
    )
    print("\nResumen de tiempos (ms):")
    print(resumen.to_string(float_format=lambda valor: f"{valor:.3f}"))


if __name__ == "__main__":
    main()
