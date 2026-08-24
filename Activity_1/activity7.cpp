#include <iostream>
#include <list>
#include <stdexcept>
using namespace std;

template <typename T>
class MyQueue {
private:
    list<T> data;

public:

    void enqueue(const T &value) {
        data.push_back(value);
    }

    void dequeue() {
        if (empty()) throw runtime_error("MyQueue::dequeue(): queue is empty");
        data.pop_front();
    }

    T& front() {
        if (empty()) throw runtime_error("MyQueue::front(): queue is empty");
        return data.front();
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }
};

int main() {
    MyQueue<int> queue;

    cout << "Testing MyQueue\n";
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    cout << "Enqueued: 1, 2, 3. Size = " << queue.size() << "\n";
    cout << "Front = " << queue.front() << "\n";

    cout << "\nDequeuing all elements:\n";
    while (!queue.empty()) {
        cout << queue.front() << " ";
        queue.dequeue();
    }
    cout << "\n";

    try {
        queue.dequeue();
    } catch (const exception &e) {
        cout << "\nCaught expected exception: " << e.what() << "\n";
    }

    return 0;
}