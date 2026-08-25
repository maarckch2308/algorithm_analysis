#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <list>
using namespace std;

int main() {

    cout << "1) std::stack (LIFO)\n---------------------\n";
    stack<int> s;
    s.push(1); s.push(2); s.push(3);
    cout << "Top = " << s.top() << "\n";
    while (!s.empty()) { cout << s.top() << " "; s.pop(); }
    cout << "\n\n";
    stack<int, vector<int>> sVec;
    sVec.push(100); sVec.push(200);
    cout << "std::stack<int, vector<int>> top = " << sVec.top() << "\n\n";

    cout << "2) std::queue (FIFO)\n---------------------\n";
    queue<int> q;
    q.push(1); q.push(2); q.push(3);
    cout << "Front = " << q.front() << ", Back = " << q.back() << "\n";
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << "\n\n";

    queue<int, list<int>> qList;
    qList.push(7); qList.push(8);
    cout << "std::queue<int, list<int>> front = " << qList.front() << "\n\n";

    cout << "3) std::deque used as both stack and queue\n"
         << "--------------------------------------------\n";
    deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);
    cout << "Deque contents (front to back): ";
    for (int v : dq) cout << v << " ";
    cout << "\n";
    cout << "As a stack -> pop_back(): removes " << dq.back() << "\n";
    dq.pop_back();
    cout << "As a queue -> pop_front(): removes " << dq.front() << "\n";
    dq.pop_front();
    cout << "\n";

    cout << "4) std::priority_queue (priority order, max-heap by default)\n"
         << "----------------------------------------------------------------\n";
    priority_queue<int> pq;
    pq.push(5); pq.push(1); pq.push(9); pq.push(3);
    cout << "Popping in priority order: ";
    while (!pq.empty()) { cout << pq.top() << " "; pq.pop(); }
    cout << "\n";

    return 0;
}