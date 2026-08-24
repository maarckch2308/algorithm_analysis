#include <iostream>
using namespace std;

int gcdIterative(int m, int n) {
    while (n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int gcdRecursive(int m, int n) {
    if (n == 0) return m;
    return gcdRecursive(n, m % n);
}

int main() {
    int testPairs[][2] = { {206, 40}, {1071, 462}, {17, 5}, {48, 18}, {0, 5} };

    cout << "Euclid's Algorithm - GCD\n";
    cout << "-------------------------\n";
    for (auto &p : testPairs) {
        int m = p[0], n = p[1];
        cout << "gcd(" << m << ", " << n << ") = "
             << gcdIterative(m, n)
             << "  (recursive check: " << gcdRecursive(m, n) << ")\n";
    }
    return 0;
}