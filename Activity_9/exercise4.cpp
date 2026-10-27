
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;

struct Edge {
    int to;
    int weight;
};

using Graph = vector<vector<Edge>>;

void dijkstra(const Graph& graph,
              const vector<string>& names,
              int source) {
    int n = static_cast<int>(graph.size());

    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);

    // Min-priority queue: {distance, vertex}
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    cout << "\nRunning Dijkstra from vertex "
         << names[source] << "...\n";

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        // Ignore outdated queue entries.
        if (currentDist != dist[u]) {
            continue;
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            long long newDist = currentDist + edge.weight;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                parent[v] = u;
                pq.push({newDist, v});
            }
        }
    }

    cout << "\n=== Shortest Paths from "
         << names[source] << " ===\n";

    for (int v = 0; v < n; v++) {
        cout << "Destination: " << names[v] << "\n";

        if (dist[v] == INF) {
            cout << "  Distance: unreachable\n";
            cout << "  Path: none\n";
            continue;
        }

        cout << "  Distance: " << dist[v] << "\n";

        vector<int> path;

        for (int current = v; current != -1;
             current = parent[current]) {
            path.push_back(current);
        }

        reverse(path.begin(), path.end());

        cout << "  Path: ";

        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) {
                cout << " -> ";
            }
            cout << names[path[i]];
        }

        cout << "\n";
    }
}

int main() {
    int n, m;
    char graphType;

    cout << "=== Dijkstra's Algorithm ===\n";
    cout << "Number of vertices: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error: the number of vertices must be positive.\n";
        return 1;
    }

    cout << "Number of edges: ";
    cin >> m;

    if (m < 0) {
        cout << "Error: the number of edges cannot be negative.\n";
        return 1;
    }

    cout << "Graph type (D = directed, U = undirected): ";
    cin >> graphType;

    graphType = static_cast<char>(
        toupper(static_cast<unsigned char>(graphType))
    );

    if (graphType != 'D' && graphType != 'U') {
        cout << "Error: enter D or U.\n";
        return 1;
    }

    vector<string> names(n);

    cout << "Enter the " << n << " vertex names:\n";
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    Graph graph(n);

    cout << "Enter each edge as: from to weight\n";

    for (int i = 0; i < m; i++) {
        string from, to;
        int weight;

        cin >> from >> to >> weight;

        int u = -1;
        int v = -1;

        for (int j = 0; j < n; j++) {
            if (names[j] == from) {
                u = j;
            }
            if (names[j] == to) {
                v = j;
            }
        }

        if (u == -1 || v == -1) {
            cout << "Error: unknown vertex name.\n";
            return 1;
        }

        if (weight < 0) {
            cout << "Error: Dijkstra requires non-negative weights.\n";
            return 1;
        }

        graph[u].push_back({v, weight});

        if (graphType == 'U') {
            graph[v].push_back({u, weight});
        }
    }

    string sourceName;
    cout << "Source vertex: ";
    cin >> sourceName;

    int source = -1;

    for (int i = 0; i < n; i++) {
        if (names[i] == sourceName) {
            source = i;
            break;
        }
    }

    if (source == -1) {
        cout << "Error: unknown source vertex.\n";
        return 1;
    }

    dijkstra(graph, names, source);

    return 0;
}
