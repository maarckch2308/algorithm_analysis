
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void distributionCountingSort(vector<int>& A) {
    if (A.empty()) {
        return;
    }

    int minValue = *min_element(A.begin(), A.end());
    int maxValue = *max_element(A.begin(), A.end());

    long long range =
        static_cast<long long>(maxValue) - minValue + 1;

    vector<int> count(static_cast<size_t>(range), 0);

    // Count the frequency of each value
    for (int value : A) {
        count[static_cast<size_t>(
            static_cast<long long>(value) - minValue
        )]++;
    }

    // Reconstruct the sorted array
    int index = 0;

    for (long long i = 0; i < range; i++) {
        while (count[static_cast<size_t>(i)] > 0) {
            A[index++] = static_cast<int>(i + minValue);
            count[static_cast<size_t>(i)]--;
        }
    }
}

int main() {
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    if (!cin || n < 0) {
        cout << "Error: enter a non-negative number of elements.\n";
        return 1;
    }

    vector<int> A(n);

    cout << "Enter " << n << " integers:\n";

    for (int i = 0; i < n; i++) {
        if (!(cin >> A[i])) {
            cout << "Error: invalid input.\n";
            return 1;
        }
    }

    distributionCountingSort(A);

    cout << "\nSorted array:\n";

    for (int value : A) {
        cout << value << " ";
    }

    cout << "\n";

    return 0;
}
