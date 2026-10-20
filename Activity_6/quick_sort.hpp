// Ejercicio 4: Implementación de Quick Sort (in-place, partición de Lomuto).
// Pivote aleatorio opcional para evitar el peor caso en listas ya ordenadas.
// La versión con pivote fijo (último elemento) sirve para el análisis empírico.
#pragma once
#include <random>
#include <utility>
#include <vector>

inline std::mt19937& qs_rng() {
    static std::mt19937 rng(2024);
    return rng;
}

template <typename T>
long partition_lomuto(std::vector<T>& a, long lo, long hi, bool randomized) {
    if (randomized) {
        long r = std::uniform_int_distribution<long>(lo, hi)(qs_rng());
        std::swap(a[r], a[hi]);
    }
    T pivot = a[hi];
    long i = lo - 1;
    for (long j = lo; j < hi; ++j) {
        if (a[j] <= pivot) {
            ++i;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i + 1], a[hi]);
    return i + 1;
}

template <typename T>
void quick_sort_rec(std::vector<T>& a, long lo, long hi, bool randomized) {
    // Se recurre sobre la rama menor y se itera sobre la mayor:
    // la profundidad de pila es O(log n) incluso en el peor caso.
    while (lo < hi) {
        long p = partition_lomuto(a, lo, hi, randomized);
        if (p - lo < hi - p) {
            quick_sort_rec(a, lo, p - 1, randomized);
            lo = p + 1;
        } else {
            quick_sort_rec(a, p + 1, hi, randomized);
            hi = p - 1;
        }
    }
}

// Ordena `a` in-place.
template <typename T>
void quick_sort(std::vector<T>& a, bool randomized = true) {
    quick_sort_rec(a, 0, static_cast<long>(a.size()) - 1, randomized);
}
