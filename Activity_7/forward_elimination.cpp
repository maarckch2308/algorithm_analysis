#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;
using Matrix = vector<vector<double>>;
using Vector = vector<double>;
const double EPS = 1e-12;
void printVector(const Vector& v) { for (double x : v) cout << fixed << setprecision(4) << x << " "; cout << '\n'; }
void printMatrix(const Matrix& A) { for (const auto& row : A) { for (double x : row) cout << setw(10) << fixed << setprecision(4) << x; cout << '\n'; } }


void forwardElimination(Matrix& A, Vector& b) {
    int n = (int)A.size();
    if (n == 0 || b.size() != A.size()) throw invalid_argument("Incompatible dimensions.");
    for (const auto& row : A) if (row.size() != A.size()) throw invalid_argument("A must be square.");
    for (int k = 0; k < n - 1; ++k) {
        int pivot = k;
        for (int i = k + 1; i < n; ++i) if (abs(A[i][k]) > abs(A[pivot][k])) pivot = i;
        if (abs(A[pivot][k]) < EPS) throw runtime_error("Zero pivot: no unique solution.");
        if (pivot != k) { swap(A[k], A[pivot]); swap(b[k], b[pivot]); }
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k]; A[i][k] = 0.0;
            for (int j = k + 1; j < n; ++j) A[i][j] -= factor * A[k][j];
            b[i] -= factor * b[k];
        }
    }
    if (abs(A[n-1][n-1]) < EPS) throw runtime_error("Zero final pivot: no unique solution.");
}
Vector backwardSubstitution(const Matrix& U, const Vector& y) {
    int n = (int)U.size(); Vector x(n, 0.0);
    for (int i=n-1; i>=0; --i) { double sum=0.0; for (int j=i+1;j<n;++j) sum += U[i][j]*x[j];
        if (abs(U[i][i]) < EPS) throw runtime_error("Zero diagonal entry."); x[i]=(y[i]-sum)/U[i][i]; }
    return x;
}
int main() {
    Matrix A{{2,1,-1},{-3,-1,2},{-2,1,2}}; Vector b{8,-11,-3};
    cout << "EXERCISE 1: FORWARD ELIMINATION\nOriginal matrix A:\n"; printMatrix(A); cout << "b = "; printVector(b);
    forwardElimination(A,b); cout << "Upper-triangular matrix U:\n"; printMatrix(A); cout << "Transformed b = "; printVector(b);
    cout << "Solution x = "; printVector(backwardSubstitution(A,b));
    return 0;
}
