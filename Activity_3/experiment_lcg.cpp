#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <limits>
#include "lcg.hpp"

using Clock = std::chrono::steady_clock;

int main() {
    LcgParams p = defaultParams(32);
    std::cout << "Fixed parameters: m=" << p.m << ", a=" << p.a
              << ", b=" << p.b << ", seed=" << p.seed << "\n\n";

    std::vector<uint64_t> nValues = {
        1000, 2000, 5000, 10000, 20000, 50000, 100000,
        200000, 500000, 1000000, 2000000
    };

    std::ofstream csv("lcg_results.csv");
    csv << "n,op_count,time_s\n";

    std::cout << std::right
              << std::setw(9) << "n" << " | "
              << std::setw(9) << "op count" << " | "
              << std::setw(10) << "time (s)" << "\n";
    std::cout << std::string(35, '-') << "\n";

    for (uint64_t n : nValues) {
        double best = std::numeric_limits<double>::infinity();
        uint64_t finalR = 0;
        for (int r = 0; r < 3; r++) {
            auto t0 = Clock::now();
            finalR = randomLcmCountOnly(n, p);
            auto t1 = Clock::now();
            double elapsed = std::chrono::duration<double>(t1 - t0).count();
            if (elapsed < best) best = elapsed;
        }
        // Prevent the compiler from treating finalR as dead: print a
        // checksum digit (harmless, keeps the computation "used").
        volatile uint64_t sink = finalR;
        (void)sink;

        uint64_t count = n; // by construction, exactly n iterations ran
        csv << n << "," << count << "," << std::setprecision(9) << best << "\n";

        std::cout << std::setw(9) << n << " | "
                  << std::setw(9) << count << " | "
                  << std::fixed << std::setprecision(6)
                  << std::setw(10) << best << "\n";
    }

    csv.close();
    std::cout << "\nSaved results to lcg_results.csv\n";
    return 0;
}
