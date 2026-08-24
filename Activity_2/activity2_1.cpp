#include <iostream>
using namespace std;

void fibonacciIterative(int n) {
    if (n < 0) {
        cout << "n must be non-negative" << endl;
        return;
    }

    long long tPrev2 = 0; // T(n-2)
    long long tPrev1 = 1; // T(n-1)
    long long tCurrent;

    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            cout << "T(" << i << ") = " << tPrev2 << endl;
        } else if (i == 1) {
            cout << "T(" << i << ") = " << tPrev1 << endl;
        } else {
            tCurrent = tPrev2 + tPrev1;
            cout << "T(" << i << ") = " << tCurrent << endl;
            tPrev2 = tPrev1;
            tPrev1 = tCurrent;
        }
    }
}

int main() {
    int n;
    cout << "Enter n (number of terms - 1, i.e. up to T(n)): ";
    cin >> n;

    fibonacciIterative(n);

    return 0;
}