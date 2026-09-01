#include <iostream>
#include <iomanip>
#include "lcg.hpp"

int main() {
    LcgParams p = defaultParams(16); // small w so numbers are easy to read

    std::cout << "Parameters: m=" << p.m << ", a=" << p.a
              << ", b=" << p.b << ", seed=" << p.seed << "\n\n";

    auto seq = randomLcmSequence(20, p);

    std::cout << "First 20 pseudo-random integers (0.." << (p.m - 1) << "):\n[";
    for (size_t i = 0; i < seq.size(); i++)
        std::cout << seq[i] << (i + 1 < seq.size() ? ", " : "");
    std::cout << "]\n\n";

    std::cout << "Basic-operation count: " << seq.size() << "\n\n";

    std::cout << "Same numbers normalized to [0,1):\n[";
    std::cout << std::fixed << std::setprecision(4);
    for (size_t i = 0; i < seq.size(); i++)
        std::cout << (double(seq[i]) / double(p.m)) << (i + 1 < seq.size() ? ", " : "");
    std::cout << "]\n";

    return 0;
}
