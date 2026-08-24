#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> myList;

    cout << "Using std::list as a queue (push_back / pop_front)\n";

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    cout << "Enqueued: 10, 20, 30\n";
    cout << "Front of queue (front()): " << myList.front() << "\n";

    cout << "\nDequeuing elements:\n";
    while (!myList.empty()) {
        cout << "Front -> " << myList.front() << "\n";
        myList.pop_front();
    }

    cout << "\nQueue is now empty: " << (myList.empty() ? "yes" : "no") << "\n";
    return 0;
}