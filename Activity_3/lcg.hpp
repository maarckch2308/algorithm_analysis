#pragma once

#include <cstdint>
#include <vector>
#include <ctime>

struct LcgParams {
    uint64_t m;
    uint64_t a;
    uint64_t b;
    uint64_t seed;
};

// Full version: builds and returns the sequence (used for demonstration).
inline std::vector<uint64_t> randomLcmSequence(uint64_t n, const LcgParams &p) {
    std::vector<uint64_t> sequence;
    sequence.reserve(n);
    uint64_t r = p.seed;
    for (uint64_t i = 0; i < n; i++) {
        r = (p.a * r + p.b) % p.m;
        sequence.push_back(r);
    }
    return sequence;
}

// Count-only version: no sequence stored, no I/O -> used for timing.
// Returns the final value of r (not just n) so the optimizer cannot
// prove the loop is a no-op and eliminate it (op_count == n always,
// verified by the caller against n directly).
inline uint64_t randomLcmCountOnly(uint64_t n, const LcgParams &p) {
    uint64_t r = p.seed;
    for (uint64_t i = 0; i < n; i++) {
        r = (p.a * r + p.b) % p.m;
    }
    return r;
}

// Textbook-style default parameters: m = 2^w, "Numerical Recipes" constants
// for a and b (satisfy the Hull-Dobell theorem for a power-of-two modulus,
// guaranteeing full period m), seed derived from current time.
inline LcgParams defaultParams(int w = 32) {
    LcgParams p;
    p.m = (w >= 64) ? UINT64_MAX : (uint64_t(1) << w);
    p.a = 1664525ULL % p.m;
    p.b = 1013904223ULL % p.m;
    if (p.b % 2 == 0) p.b += 1;
    p.seed = static_cast<uint64_t>(std::time(nullptr)) % p.m;
    return p;
}
