#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(int start, const vector<vector<int>>& graph) {
    int V = static_cast<int>(graph.size());

    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int V = 6;

    vector<vector<int>> graph(V);

    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0};
    graph[3] = {1};
    graph[4] = {1, 5};
    graph[5] = {4};

    cout << "BFS traversal: ";
    BFS(0, graph);
    cout << endl;

    return 0;
}
