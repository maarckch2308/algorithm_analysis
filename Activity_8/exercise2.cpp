
#include <iostream>
#include <vector>
using namespace std;

void comparisonCountingSort(vector<int>& A) {
    int n = static_cast<int>(A.size());

    vector<int> count(n, 0);
    vector<int> S(n);

    // Count how many elements are smaller than each element
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A[i] <= A[j]) {
                count[j]++;
            } else {
                count[i]++;
            }
        }
    }

    // Place each element in its correct position
    for (int i = 0; i < n; i++) {
        S[count[i]] = A[i];
    }

    A = S;
}

int main() {
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    if (n < 0) {
        cout << "Error: the number of elements cannot be negative.\n";
        return 1;
    }

    vector<int> A(n);

    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    comparisonCountingSort(A);

    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";

    return 0;
}
