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

struct LUResult { Matrix L, U; vector<int> permutation; };

LUResult luDecomposition(Matrix A) {
    int n=(int)A.size(); if(n==0) throw invalid_argument("A must be nonempty.");
    for(const auto& row:A) if(row.size()!=A.size()) throw invalid_argument("A must be square.");
    Matrix L(n,Vector(n,0.0)); vector<int> p(n); for(int i=0;i<n;++i){L[i][i]=1.0;p[i]=i;}
    for(int k=0;k<n;++k){
        int pivot=k; for(int i=k+1;i<n;++i) if(abs(A[i][k])>abs(A[pivot][k])) pivot=i;
        if(abs(A[pivot][k])<EPS) throw runtime_error("Singular matrix.");
        if(pivot!=k){swap(A[k],A[pivot]);swap(p[k],p[pivot]);for(int j=0;j<k;++j)swap(L[k][j],L[pivot][j]);}
        for(int i=k+1;i<n;++i){double factor=A[i][k]/A[k][k];L[i][k]=factor;A[i][k]=0.0;for(int j=k+1;j<n;++j)A[i][j]-=factor*A[k][j];}
    } return {L,A,p};
}
Vector forwardSubstitution(const Matrix& L,const Vector& b){int n=(int)L.size();Vector y(n,0.0);for(int i=0;i<n;++i){double s=0;for(int j=0;j<i;++j)s+=L[i][j]*y[j];if(abs(L[i][i])<EPS)throw runtime_error("Zero diagonal.");y[i]=(b[i]-s)/L[i][i];}return y;}
Vector backwardSubstitution(const Matrix& U,const Vector& y){int n=(int)U.size();Vector x(n,0.0);for(int i=n-1;i>=0;--i){double s=0;for(int j=i+1;j<n;++j)s+=U[i][j]*x[j];if(abs(U[i][i])<EPS)throw runtime_error("Zero diagonal.");x[i]=(y[i]-s)/U[i][i];}return x;}
Vector solveLU(const Matrix& A,const Vector& b){LUResult lu=luDecomposition(A);Vector pb(b.size());for(size_t i=0;i<b.size();++i)pb[i]=b[lu.permutation[i]];return backwardSubstitution(lu.U,forwardSubstitution(lu.L,pb));}
int main(){
    Matrix A{{2,1,1},{4,-6,0},{-2,7,2}}; Vector b{5,-2,9}; LUResult lu=luDecomposition(A);
    cout<<"EXERCISE 4: LU DECOMPOSITION\nL matrix:\n";printMatrix(lu.L);cout<<"U matrix:\n";printMatrix(lu.U);
    cout<<"Solution x = ";printVector(solveLU(A,b));cout<<"Expected solution: 1 1 2\nTime complexity: O(n^3) for factorization\n";return 0;
}
