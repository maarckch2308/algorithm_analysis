#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <stack>

using Move = std::pair<char, char>;

// ---------------------------------------------------------------- Recursive
inline void hanoiRecursiveImpl(int n, char source, char auxiliary, char target,
                                uint64_t &counter, std::vector<Move> *moves) {
    if (n == 1) {
        counter++;
        if (moves) moves->push_back({source, target});
        return;
    }
    hanoiRecursiveImpl(n - 1, source, target, auxiliary, counter, moves);
    counter++;
    if (moves) moves->push_back({source, target});
    hanoiRecursiveImpl(n - 1, auxiliary, source, target, counter, moves);
}

// Full version: also builds the move list (used for small n / demonstration).
inline uint64_t hanoiRecursive(int n, std::vector<Move> &moves) {
    uint64_t counter = 0;
    hanoiRecursiveImpl(n, 'A', 'B', 'C', counter, &moves);
    return counter;
}

// Count-only version: no move list built, no I/O -> used for timing at large n.
inline uint64_t hanoiRecursiveCountOnly(int n) {
    uint64_t counter = 0;
    hanoiRecursiveImpl(n, 'A', 'B', 'C', counter, nullptr);
    return counter;
}

// ---------------------------------------------------------------- Iterative
// Peg-cycling technique:
//   - if n is even, the smallest disk cycles A -> B -> C -> A ...
//   - if n is odd,  the smallest disk cycles A -> C -> B -> A ...
//   - every other move is the only legal move that does not touch
//     the smallest disk.
// This reproduces the same optimal 2^n - 1 moves with O(1) extra
// space (three stacks of disks) instead of O(n) recursion depth.
inline uint64_t hanoiIterative(int n, std::vector<Move> *moves) {
    std::vector<int> pegs[3]; // 0='A', 1='B', 2='C'  (back() = top of peg)
    for (int d = n; d >= 1; d--) pegs[0].push_back(d);

    char cycle[4];
    if (n % 2 == 0) { cycle[0]='A'; cycle[1]='B'; cycle[2]='C'; cycle[3]='A'; }
    else            { cycle[0]='A'; cycle[1]='C'; cycle[2]='B'; cycle[3]='A'; }

    auto idx = [](char c) { return c - 'A'; };

    uint64_t totalMoves = (uint64_t(1) << n) - 1;
    uint64_t moveCount = 0;

    for (uint64_t i = 0; i < totalMoves; i++) {
        int step = i % 3;
        char cFrom = cycle[step], cTo = cycle[step + 1];
        int pFrom = idx(cFrom), pTo = idx(cTo);

        bool fromEmpty = pegs[pFrom].empty();
        bool toEmpty = pegs[pTo].empty();
        int topFrom = fromEmpty ? INT32_MAX : pegs[pFrom].back();
        int topTo = toEmpty ? INT32_MAX : pegs[pTo].back();

        // Determine legal direction: the smaller disk must end on top.
        if (fromEmpty || (!toEmpty && topTo < topFrom)) {
            std::swap(pFrom, pTo);
            std::swap(cFrom, cTo);
        }

        int disk = pegs[pFrom].back();
        pegs[pFrom].pop_back();
        pegs[pTo].push_back(disk);
        moveCount++;
        if (moves) moves->push_back({cFrom, cTo});
    }
    return moveCount;
}

inline uint64_t hanoiIterativeCountOnly(int n) {
    return hanoiIterative(n, nullptr);
}
