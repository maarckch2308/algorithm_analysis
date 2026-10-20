// Pruebas del Ejercicio 4: Quick Sort contra std::sort.
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>
#include "quick_sort.hpp"

int main() {
    std::mt19937 rng(1);
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Listas aleatorias de distintos tamaños (incluye vacía y de 1 elemento)
    for (int n : {0, 1, 2, 10, 100, 1000, 10000}) {
        std::vector<int> data(n);
        for (int& x : data) x = dist(rng);
        std::vector<int> expected = data;
        std::sort(expected.begin(), expected.end());

        std::vector<int> a = data, b = data;
        quick_sort(a, true);
        quick_sort(b, false);
        assert(a == expected);
        assert(b == expected);
        std::cout << "n=" << std::setw(6) << n << ": OK\n";
    }

    std::vector<int> sample(15);
    for (int& x : sample) x = std::uniform_int_distribution<int>(0, 100)(rng);
    std::cout << "\nOriginal : ";
    for (int x : sample) std::cout << x << ' ';
    quick_sort(sample);
    std::cout << "\nOrdenada : ";
    for (int x : sample) std::cout << x << ' ';
    std::cout << "\nTodas las pruebas pasaron.\n";
    return 0;
}
