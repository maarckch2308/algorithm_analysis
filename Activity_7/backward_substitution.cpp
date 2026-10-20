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


Vector backwardSubstitution(const Matrix& U, const Vector& y) {
    int n=(int)U.size(); if(n==0 || y.size()!=U.size()) throw invalid_argument("Incompatible dimensions.");
    for (const auto& row:U) if(row.size()!=U.size()) throw invalid_argument("U must be square.");
    Vector x(n,0.0);
    for(int i=n-1;i>=0;--i) {
        if(abs(U[i][i])<EPS) throw runtime_error("Zero diagonal entry.");
        double sum=0.0; for(int j=i+1;j<n;++j) sum += U[i][j]*x[j];
        x[i]=(y[i]-sum)/U[i][i];
    }
    return x;
}
int main() {
    Matrix U{{2,1,-1},{0,2,1},{0,0,3}}; Vector y{3,5,6};
    cout << "EXERCISE 2: BACKWARD SUBSTITUTION\nUpper-triangular U:\n"; printMatrix(U); cout << "y = "; printVector(y);
    cout << "Solution x = "; printVector(backwardSubstitution(U,y));
    cout << "Running time: Theta(n^2)\n";
    return 0;
}
