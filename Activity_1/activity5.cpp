#include <iostream>
#include <list>
#include <stdexcept>
using namespace std;

template <typename T>
class MyStack {
private:
    list<T> data;

public:

    void push(const T &value) {
        data.push_back(value);
    }

    void pop() {
        if (empty()) throw runtime_error("MyStack::pop(): stack is empty");
        data.pop_back();
    }

    T& top() {
        if (empty()) throw runtime_error("MyStack::top(): stack is empty");
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }
};

int main() {
    MyStack<int> stack;

    cout << "Testing MyStack\n";
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << "Pushed: 1, 2, 3. Size = " << stack.size() << "\n";
    cout << "Top = " << stack.top() << "\n";

    cout << "\nPopping all elements:\n";
    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << "\n";

    try {
        stack.pop();
    } catch (const exception &e) {
        cout << "\nCaught expected exception: " << e.what() << "\n";
    }

    return 0;
}