// Ejercicio 3: ¿Merge Sort es estable?
// Un algoritmo es estable si los elementos con la misma clave conservan su
// orden relativo original. Se ordenan registros (nombre, nota) por nota.
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>
#include "merge_sort.hpp"

struct Record {
    std::string name;
    int key;
    bool operator==(const Record& o) const { return name == o.name && key == o.key; }
};

// Verifica que, para cada clave, el orden relativo se mantenga.
bool is_stable(const std::vector<Record>& original, const std::vector<Record>& ordered) {
    std::map<int, std::vector<Record>> go, gs;
    for (const auto& r : original) go[r.key].push_back(r);
    for (const auto& r : ordered)  gs[r.key].push_back(r);
    return go == gs;
}

void print(const std::vector<Record>& v) {
    for (const auto& r : v) std::cout << "   (" << r.name << ", " << r.key << ")\n";
}

int main() {
    auto by_key = [](const Record& a, const Record& b) { return a.key < b.key; };

    // --- Ejemplo concreto ---
    std::vector<Record> students = {
        {"Ana", 90}, {"Beto", 85}, {"Carla", 90},
        {"Diego", 85}, {"Elena", 70}, {"Fabian", 90},
    };

    std::cout << "Original:\n";
    print(students);

    auto result = merge_sort(students, by_key);
    std::cout << "\nOrdenado por nota con Merge Sort:\n";
    print(result);
    std::cout << "\n¿Estable en el ejemplo? -> " << std::boolalpha
              << is_stable(students, result) << "\n";

    // --- Experimento masivo con muchos empates ---
    std::mt19937 rng(42);
    bool all_stable = true;
    for (int t = 0; t < 1000 && all_stable; ++t) {
        int n = std::uniform_int_distribution<int>(2, 60)(rng);
        std::vector<Record> data;
        for (int i = 0; i < n; ++i)
            data.push_back({std::to_string(i), std::uniform_int_distribution<int>(0, 5)(rng)});
        auto out = merge_sort(data, by_key);
        if (!is_stable(data, out)) all_stable = false;
    }
    std::cout << "1000 pruebas aleatorias con muchos empates -> estable: " << all_stable << "\n";

    // --- Contraste: usar "<" en lugar de "<=" en la mezcla pierde la estabilidad ---
    auto bad = merge_sort(students, by_key, /*strict=*/true);
    std::cout << "\nContraste con '<' en lugar de '<=':\n";
    print(bad);
    std::cout << "  ¿Estable? -> " << is_stable(students, bad) << "\n";
    return 0;
}
