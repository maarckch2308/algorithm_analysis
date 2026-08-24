#include <iostream>
#include <algorithm>
using namespace std;

int gcdConsecutiveIntegerChecking(int m, int n) {
    int t = min(m, n);
    while (t > 0) {
        if (m % t == 0 && n % t == 0) {
            return t;
        }
        t--;
    }
    return 1; 
}

int main() {
    int testPairs[][2] = { {206, 40}, {1071, 462}, {17, 5}, {48, 18}, {60, 24} };

    cout << "Consecutive Integer Checking Algorithm - GCD\n";
    cout << "---------------------------------------------\n";
    for (auto &p : testPairs) {
        int m = p[0], n = p[1];
        cout << "gcd(" << m << ", " << n << ") = "
             << gcdConsecutiveIntegerChecking(m, n) << "\n";
    }
    return 0;
}