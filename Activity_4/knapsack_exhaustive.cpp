#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Result {
    long long value;
    long long weight;
};

Result knapsackExhaustive(const vector<int>& weights,
                          const vector<int>& values,
                          int index,
                          int capacity) {
    if (index == static_cast<int>(weights.size())) {
        return {0, 0};
    }

    Result without = knapsackExhaustive(
        weights, values, index + 1, capacity
    );

    Result with = {-1, 0};

    if (weights[index] <= capacity) {
        Result next = knapsackExhaustive(
            weights, values, index + 1,
            capacity - weights[index]
        );

        with.value = values[index] + next.value;
        with.weight = weights[index] + next.weight;
    }

    return (with.value > without.value) ? with : without;
}

int main() {
    mt19937 generator(42);

    uniform_int_distribution<int> weightDist(1, 50);
    uniform_int_distribution<int> valueDist(1, 100);

    const double TIME_LIMIT = 30.0;

    cout << fixed << setprecision(6);
    cout << "n\tCapacity\tTime (seconds)\tBest Value\n";
    cout << "------------------------------------------------------\n";

    for (int n = 3; ; ++n) {
        vector<int> weights(n);
        vector<int> values(n);

        int totalWeight = 0;

        for (int i = 0; i < n; ++i) {
            weights[i] = weightDist(generator);
            values[i] = valueDist(generator);
            totalWeight += weights[i];
        }

        int capacity = totalWeight / 2;

        auto start = high_resolution_clock::now();

        Result answer = knapsackExhaustive(
            weights, values, 0, capacity
        );

        auto end = high_resolution_clock::now();

        double elapsed =
            duration<double>(end - start).count();

        cout << n << "\t"
             << capacity << "\t\t"
             << elapsed << "\t\t"
             << answer.value << "\n";

        if (elapsed >= TIME_LIMIT) {
            cout << "\nExecution reached approximately "
                 << TIME_LIMIT << " seconds.\n";
            break;
        }
    }

    return 0;
}