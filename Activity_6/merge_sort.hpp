// Ejercicio 2: Implementación de Merge Sort.
// Acepta un comparador "menor que" opcional para ordenar registros
// (útil para probar la estabilidad en el ejercicio 3).
#pragma once
#include <functional>
#include <vector>

// Mezcla dos mitades ordenadas. `strict` = true usa "<" (rompe la estabilidad);
// con false (por defecto) se usa "<=" mediante !less(right, left), que es estable.
template <typename T, typename Less>
std::vector<T> merge_halves(const std::vector<T>& left, const std::vector<T>& right,
                            Less less, bool strict = false) {
    std::vector<T> result;
    result.reserve(left.size() + right.size());
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        // Estable: ante un empate se toma primero el elemento de la mitad izquierda
        // (equivale a key(left) <= key(right)).
        bool take_left = strict ? less(left[i], right[j]) : !less(right[j], left[i]);
        if (take_left) result.push_back(left[i++]);
        else           result.push_back(right[j++]);
    }
    while (i < left.size())  result.push_back(left[i++]);
    while (j < right.size()) result.push_back(right[j++]);
    return result;
}

// Devuelve una nueva lista ordenada (no modifica la original).
template <typename T, typename Less = std::less<T>>
std::vector<T> merge_sort(const std::vector<T>& arr, Less less = Less(), bool strict = false) {
    if (arr.size() <= 1) return arr;
    size_t mid = arr.size() / 2;
    std::vector<T> left (arr.begin(), arr.begin() + mid);
    std::vector<T> right(arr.begin() + mid, arr.end());
    return merge_halves(merge_sort(left, less, strict), merge_sort(right, less, strict), less, strict);
}
