// Prueba del Ejercicio 2: Merge Sort contra std::sort.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include "merge_sort.hpp"

int main() {
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(0, 100);

    std::vector<int> data(15);
    for (int& x : data) x = dist(rng);

    std::vector<int> sorted_mine = merge_sort(data);
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    std::cout << "Original : ";
    for (int x : data) std::cout << x << ' ';
    std::cout << "\nOrdenada : ";
    for (int x : sorted_mine) std::cout << x << ' ';
    std::cout << '\n';

    assert(sorted_mine == expected);
    std::cout << "OK: coincide con std::sort\n";
    return 0;
}
