
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DisjointSet {
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        return true;
    }
};

void kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(V);
    vector<Edge> mst;
    int totalWeight = 0;

    for (const Edge& edge : edges) {
        if (ds.unite(edge.src, edge.dest)) {
            mst.push_back(edge);
            totalWeight += edge.weight;

            if (mst.size() == V - 1) {
                break;
            }
        }
    }

    if (mst.size() != V - 1) {
        cout << "Graph is disconnected. MST cannot be formed.\n";
        return;
    }

    cout << "\nMinimum Spanning Tree (Kruskal's Algorithm):\n";
    cout << "Edge \tWeight\n";

    for (const Edge& edge : mst) {
        cout << edge.src << " - " << edge.dest
             << "\t" << edge.weight << '\n';
    }

    cout << "Total MST Weight: " << totalWeight << '\n';
}

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> E;

    if (E < 0) {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<Edge> edges;

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertex number.\n";
            return 0;
        }

        edges.push_back({u, v, w});
    }

    kruskalMST(V, edges);

    return 0;
}
