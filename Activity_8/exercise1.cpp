
#include <iostream>
using namespace std;

int main() {
    int u, v;

    cout << "Enter the value of u: ";
    cin >> u;

    cout << "Enter the value of v: ";
    cin >> v;

    cout << "\nBefore swapping:\n";
    cout << "u = " << u << "\n";
    cout << "v = " << v << "\n";

    // Swap without using an auxiliary variable
    u = u ^ v;
    v = u ^ v;
    u = u ^ v;

    cout << "\nAfter swapping:\n";
    cout << "u = " << u << "\n";
    cout << "v = " << v << "\n";

    return 0;
}
