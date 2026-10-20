#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include "quick_sort.hpp"

using Clock = std::chrono::steady_clock;
static std::mt19937 rng(7);

static const std::vector<long> sizes = {500, 1000, 2000, 4000, 8000, 16000, 32000,
                                        64000, 128000};
static const int REPS = 5;

std::vector<int> random_list(long n) {
    std::vector<int> v(n);
    std::uniform_int_distribution<int> d(0, 1000000);
    for (int& x : v) x = d(rng);
    return v;
}

std::vector<int> sorted_list(long n) {
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    return v;
}

// Mejor tiempo (segundos) de REPS repeticiones para cada tamaño.
std::vector<double> measure(const std::function<std::vector<int>(long)>& make, bool randomized) {
    std::vector<double> times;
    for (long n : sizes) {
        double best = std::numeric_limits<double>::infinity();
        for (int r = 0; r < REPS; ++r) {
            auto data = make(n);
            auto t0 = Clock::now();
            quick_sort(data, randomized);
            double dt = std::chrono::duration<double>(Clock::now() - t0).count();
            best = std::min(best, dt);
        }
        times.push_back(best);
    }
    return times;
}

void print_ratios(const std::string& name, const std::vector<double>& ts) {
    std::cout << "  " << std::left << std::setw(24) << name << std::right;
    double sum = 0;
    for (size_t i = 0; i + 1 < ts.size(); ++i) {
        double r = ts[i + 1] / ts[i];
        sum += r;
        std::cout << std::setw(6) << std::fixed << std::setprecision(2) << r << ' ';
    }
    std::cout << "| promedio " << sum / (ts.size() - 1) << "\n";
}

int main() {
    auto t_random       = measure(random_list, true);
    auto t_sorted_fixed = measure(sorted_list, false);  // peor caso
    auto t_sorted_rand  = measure(sorted_list, true);

    std::cout << std::setw(7) << "n" << " | " << std::setw(10) << "aleatoria" << " | "
              << std::setw(12) << "t/(n lg n)" << " | " << std::setw(16) << "ord. pivote fijo"
              << " | " << std::setw(10) << "t/n^2" << " | " << std::setw(18)
              << "ord. pivote aleat." << "\n"
              << std::string(90, '-') << "\n";
    for (size_t i = 0; i < sizes.size(); ++i) {
        double n = static_cast<double>(sizes[i]);
        std::cout << std::setw(7) << sizes[i] << " | " << std::setw(10) << std::fixed
                  << std::setprecision(5) << t_random[i] << " | " << std::setw(12)
                  << std::scientific << std::setprecision(3) << t_random[i] / (n * std::log2(n))
                  << " | " << std::setw(16) << std::fixed << std::setprecision(5)
                  << t_sorted_fixed[i] << " | " << std::setw(10) << std::scientific
                  << std::setprecision(3) << t_sorted_fixed[i] / (n * n) << " | "
                  << std::setw(18) << std::fixed << std::setprecision(5) << t_sorted_rand[i]
                  << "\n";
    }

    std::cout << "\nFactor de crecimiento al duplicar n (teórico: n log n ≈ 2.1, n² = 4):\n";
    print_ratios("aleatoria", t_random);
    print_ratios("ordenada, pivote fijo", t_sorted_fixed);

    std::ofstream csv("resultados.csv");
    csv << "n,aleatoria,ordenada_pivote_fijo,ordenada_pivote_aleatorio\n";
    for (size_t i = 0; i < sizes.size(); ++i)
        csv << sizes[i] << ',' << t_random[i] << ',' << t_sorted_fixed[i] << ','
            << t_sorted_rand[i] << "\n";
    std::cout << "\nDatos guardados en resultados.csv\n";
    return 0;
}
