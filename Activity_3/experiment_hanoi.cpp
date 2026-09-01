#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <limits>
#include "hanoi.hpp"

using Clock = std::chrono::steady_clock;

template <typename Fn>
double timeIt(Fn fn, int repeats, uint64_t &outResult) {
    double best = std::numeric_limits<double>::infinity();
    for (int r = 0; r < repeats; r++) {
        auto t0 = Clock::now();
        uint64_t result = fn();
        auto t1 = Clock::now();
        double elapsed = std::chrono::duration<double>(t1 - t0).count();
        if (elapsed < best) best = elapsed;
        outResult = result;
    }
    return best;
}

int main() {
    std::ofstream csv("hanoi_results.csv");
    csv << "n,expected_2n_minus_1,recursive_moves,iterative_moves,"
           "recursive_time_s,iterative_time_s\n";

    std::cout << std::right
              << std::setw(3) << "n" << " | "
              << std::setw(10) << "2^n-1" << " | "
              << std::setw(10) << "rec moves" << " | "
              << std::setw(10) << "it moves" << " | "
              << std::setw(13) << "rec time (s)" << " | "
              << std::setw(13) << "it time (s)" << "\n";
    std::cout << std::string(75, '-') << "\n";

    bool allConsistent = true;

    for (int n = 1; n <= 22; n++) {
        uint64_t expected = (uint64_t(1) << n) - 1;

        uint64_t recCount = 0, itCount = 0;
        double recTime = timeIt([n]() { return hanoiRecursiveCountOnly(n); }, 3, recCount);
        double itTime = timeIt([n]() { return hanoiIterativeCountOnly(n); }, 3, itCount);

        bool ok = (recCount == expected) && (itCount == expected);
        allConsistent = allConsistent && ok;

        csv << n << "," << expected << "," << recCount << "," << itCount << ","
            << std::setprecision(9) << recTime << "," << itTime << "\n";

        std::cout << std::setw(3) << n << " | "
                  << std::setw(10) << expected << " | "
                  << std::setw(10) << recCount << " | "
                  << std::setw(10) << itCount << " | "
                  << std::fixed << std::setprecision(6)
                  << std::setw(13) << recTime << " | "
                  << std::setw(13) << itTime << "\n";
    }

    csv.close();
    std::cout << "\nSaved results to hanoi_results.csv\n";
    std::cout << "Consistency check: recursive_moves == iterative_moves == 2^n - 1 for all n -> "
              << (allConsistent ? "true" : "false") << "\n";
    return 0;
}
