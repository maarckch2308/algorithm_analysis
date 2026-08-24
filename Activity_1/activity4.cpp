#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> myList;

    cout << "Using std::list as a stack (push_back / pop_back)\n";

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    cout << "Pushed: 10, 20, 30\n";
    cout << "Top of stack (back()): " << myList.back() << "\n";

    cout << "\nPopping elements:\n";
    while (!myList.empty()) {
        cout << "Top -> " << myList.back() << "\n";
        myList.pop_back(); 
    }

    cout << "\nStack is now empty: " << (myList.empty() ? "yes" : "no") << "\n";
    return 0;
}