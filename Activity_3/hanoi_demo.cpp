#include <iostream>
#include <cstdint>
#include "hanoi.hpp"

int main(int argc, char *argv[]) {
    int n = (argc > 1) ? std::stoi(argv[1]) : 4;

    std::cout << "Towers of Hanoi with n = " << n << " disks\n\n";

    std::vector<Move> recMoves, itMoves;
    uint64_t recCount = hanoiRecursive(n, recMoves);
    uint64_t itCount = hanoiIterative(n, &itMoves);
    uint64_t expected = (uint64_t(1) << n) - 1;

    std::cout << "Recursive  -> moves = " << recCount
              << "  (expected 2^n - 1 = " << expected << ")\n";
    std::cout << "Iterative  -> moves = " << itCount
              << "  (expected 2^n - 1 = " << expected << ")\n\n";

    bool ok = (recCount == itCount) && (recCount == expected);
    std::cout << "Both methods agree: " << (ok ? "true" : "false") << "\n";

    if (n <= 4) {
        std::cout << "\nRecursive move sequence:\n";
        for (size_t i = 0; i < recMoves.size(); i++)
            std::cout << "  " << (i + 1) << ": " << recMoves[i].first
                      << " -> " << recMoves[i].second << "\n";

        std::cout << "\nIterative move sequence:\n";
        for (size_t i = 0; i < itMoves.size(); i++)
            std::cout << "  " << (i + 1) << ": " << itMoves[i].first
                      << " -> " << itMoves[i].second << "\n";
    }
    return 0;
}
