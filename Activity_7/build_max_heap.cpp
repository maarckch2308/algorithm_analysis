#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

void siftDown(vector<int>& a, int n, int i) {
    while (true) {
        int largest=i, left=2*i+1, right=2*i+2;
        if(left<n && a[left]>a[largest]) largest=left;
        if(right<n && a[right]>a[largest]) largest=right;
        if(largest==i) break;
        swap(a[i],a[largest]); i=largest;
    }
}

void buildMaxHeap(vector<int>& a) { for(int i=(int)a.size()/2-1;i>=0;--i) siftDown(a,(int)a.size(),i); }
bool isMaxHeap(const vector<int>& a) {
    for(size_t i=0;i<a.size();++i) { size_t l=2*i+1,r=2*i+2; if(l<a.size()&&a[i]<a[l]) return false; if(r<a.size()&&a[i]<a[r]) return false; } return true;
}
void printArray(const vector<int>& a) { for(int x:a) cout<<x<<' '; cout<<'\n'; }
int main() {
    mt19937 rng(random_device{}()); uniform_int_distribution<int> dist(1,99); vector<int> a(12);
    for(int& x:a) x=dist(rng);
    cout << "EXERCISE 3: BUILD A MAX HEAP\nRandom array: "; printArray(a);
    buildMaxHeap(a); cout << "Max heap array: "; printArray(a);
    cout << "Valid max heap: " << boolalpha << isMaxHeap(a) << "\nBuild-heap time: O(n)\n"; return 0;
}
