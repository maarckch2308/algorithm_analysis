#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

vector<int> sieveOfEratosthenes(int limit) {
    vector<bool> isComposite(limit + 1, false);
    vector<int> primes;

    for (int i = 2; i <= limit; i++) {
        if (!isComposite[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= limit; j += i) {
                isComposite[j] = true;
            }
        }
    }
    return primes;
}

map<int, int> primeFactorization(int n, const vector<int> &primes) {
    map<int, int> factors;
    for (int p : primes) {
        if ((long long)p * p > n) break;
        while (n % p == 0) {
            factors[p]++;
            n /= p;
        }
    }
    if (n > 1) factors[n]++;
    return factors;
}

int gcdMiddleSchool(int m, int n) {
    int limit = (int)ceil(sqrt(max(m, n))) + 1;
    vector<int> primes = sieveOfEratosthenes(limit);

    map<int, int> factorsM = primeFactorization(m, primes);
    map<int, int> factorsN = primeFactorization(n, primes);

    int result = 1;
    for (auto &entry : factorsM) {
        int prime = entry.first;
        int expM = entry.second;
        auto it = factorsN.find(prime);
        if (it != factorsN.end()) {
            int expN = it->second;
            int commonExp = min(expM, expN);
            for (int i = 0; i < commonExp; i++) result *= prime;
        }
    }
    return result;
}

int main() {
    cout << "Sieve of Eratosthenes - primes up to 50\n";
    vector<int> primes = sieveOfEratosthenes(50);
    for (int p : primes) cout << p << " ";
    cout << "\n\n";

    cout << "Middle-School Procedure Algorithm - GCD\n";
    int testPairs[][2] = { {206, 40}, {1071, 462}, {60, 24}, {17, 5} };
    for (auto &p : testPairs) {
        int m = p[0], n = p[1];
        cout << "gcd(" << m << ", " << n << ") = " << gcdMiddleSchool(m, n) << "\n";
    }
    return 0;
}