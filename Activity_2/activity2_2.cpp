#include <iostream>
using namespace std;

long long fibonacciRecursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacciRecursive(n - 2) + fibonacciRecursive(n - 1);
}

int main() {
    int n;
    cout << "Enter n (number of terms - 1, i.e. up to T(n)): ";
    cin >> n;

    if (n < 0) {
        cout << "n must be non-negative" << endl;
        return 0;
    }

    for (int i = 0; i <= n; i++) {
        cout << "T(" << i << ") = " << fibonacciRecursive(i) << endl;
    }

    return 0;
}