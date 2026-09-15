#include <iostream>
#include <vector>

using namespace std;

void DFS(int node,
         const vector<vector<int>>& graph,
         vector<bool>& visited) {
    visited[node] = true;

    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            DFS(neighbor, graph, visited);
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

    vector<bool> visited(V, false);

    cout << "DFS traversal: ";
    DFS(0, graph, visited);
    cout << endl;

    return 0;
}
