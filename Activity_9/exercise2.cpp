#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
};

struct Item {
    int key;
    int vertex;

    bool operator>(const Item& other) const {
        if (key != other.key) {
            return key > other.key;
        }
        return vertex > other.vertex;
    }
};

void prim(const vector<vector<Edge>>& graph,
          const vector<string>& names,
          int start) {

    int n = static_cast<int>(graph.size());

    vector<int> key(n, INF);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    priority_queue<Item, vector<Item>, greater<Item>> pq;

    key[start] = 0;
    pq.push({0, start});

    int totalWeight = 0;
    int edgesSelected = 0;

    cout << "\n=== Prim's Minimum Spanning Tree ===\n";
    cout << "Starting vertex: " << names[start] << "\n\n";

    while (!pq.empty()) {
        Item current = pq.top();
        pq.pop();

        int u = current.vertex;

        // Ignore outdated entries or vertices already in the tree.
        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;

        if (parent[u] != -1) {
            cout << "Selected edge: "
                 << names[parent[u]] << " - " << names[u]
                 << " (weight " << key[u] << ")\n";

            totalWeight += key[u];
            edgesSelected++;
        } else {
            cout << "Starting vertex added: " << names[u] << "\n";
        }

        // Update the best connection for each neighbor.
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }

        // Show the current best keys of vertices outside the tree.
        cout << "Vertices not yet in the tree:\n";

        bool found = false;

        for (int v = 0; v < n; v++) {
            if (!inMST[v]) {
                found = true;
                cout << "  " << names[v] << ": ";

                if (key[v] == INF) {
                    cout << "INF";
                } else {
                    cout << key[v];
                }

                cout << "\n";
            }
        }

        if (!found) {
            cout << "  None\n";
        }

        cout << "-----------------------------\n";
    }

    cout << "\n=== Final Result ===\n";

    if (edgesSelected != n - 1) {
        cout << "The graph is disconnected; no spanning tree exists.\n";
        return;
    }

    cout << "Edges in the minimum spanning tree:\n";

    for (int v = 0; v < n; v++) {
        if (parent[v] != -1) {
            cout << names[parent[v]] << " - " << names[v]
                 << " (weight " << key[v] << ")\n";
        }
    }

    cout << "Total weight: " << totalWeight << "\n";
    cout << "Number of edges: " << edgesSelected << "\n";
}

int main() {
    // Vertices: a=0, b=1, c=2, d=3, e=4
    vector<string> names = {"a", "b", "c", "d", "e"};

    vector<vector<Edge>> graph(5);

    auto addEdge = [&](int u, int v, int weight) {
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    };

    // Undirected weighted graph from Exercise 1.
    addEdge(0, 1, 5);  // a-b
    addEdge(0, 2, 7);  // a-c
    addEdge(0, 4, 2);  // a-e
    addEdge(1, 3, 6);  // b-d
    addEdge(1, 4, 3);  // b-e
    addEdge(2, 3, 4);  // c-d
    addEdge(2, 4, 4);  // c-e
    addEdge(3, 4, 5);  // d-e

    prim(graph, names, 0);

    return 0;
}
