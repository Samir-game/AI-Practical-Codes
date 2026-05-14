#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// /*
// ====================================================
// Program implements:
// 1. Selection Sort
// 2. Minimum Spanning Tree (Kruskal's Algorithm)
// ====================================================
// */

// // -------------------- Selection Sort --------------------
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

// // -------------------- MST using Kruskal --------------------
struct Edge {
    int u, v, weight;
};

bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DSU {
private:
    vector<int> parent, rankArr;

public:
    DSU(int n) {
        parent.resize(n);
        rankArr.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return;

        if (rankArr[px] < rankArr[py]) {
            parent[px] = py;
        }
        else if (rankArr[px] > rankArr[py]) {
            parent[py] = px;
        }
        else {
            parent[py] = px;
            rankArr[px]++;
        }
    }
};

void kruskalMST(int vertices, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdge);

    DSU dsu(vertices);

    int totalCost = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (Edge e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            cout << e.u << " - " << e.v << " : " << e.weight << endl;
            totalCost += e.weight;
        }
    }

    cout << "Total Cost of MST = " << totalCost << endl;
}

// // -------------------- Main --------------------
int main() {
    int choice;

    cout << "Choose Operation:\n";
    cout << "1. Selection Sort\n";
    cout << "2. Minimum Spanning Tree\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int n;
        cout << "Enter number of elements: ";
        cin >> n;

        vector<int> arr(n);

        cout << "Enter elements:\n";
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        selectionSort(arr);

        cout << "Sorted Array:\n";
        for (int x : arr)
            cout << x << " ";

        cout << endl;
    }

    else if (choice == 2) {
        int v, e;
        cout << "Enter number of vertices: ";
        cin >> v;

        cout << "Enter number of edges: ";
        cin >> e;

        vector<Edge> edges(e);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < e; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        }

        kruskalMST(v, edges);
    }

    else {
        cout << "Invalid Choice";
    }

    return 0;
}


/*
struct Edge {
    int to, weight;
};
void primMST(int vertices, vector<vector<Edge>>& graph) {
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    vector<int> key(vertices, INT_MAX);
    vector<int> parent(vertices, -1);
    vector<bool> inMST(vertices, false);

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    int totalCost = 0;

    cout << "\nEdges in Prim's MST:\n";
    for (int i = 1; i < vertices; i++) {
        cout << parent[i] << " - " << i << " : " << key[i] << endl;
        totalCost += key[i];
    }

    cout << "Total Cost = " << totalCost << endl;
}

int main(){
        int v, e;
        cout << "Enter number of vertices: ";
        cin >> v;

        cout << "Enter number of edges: ";
        cin >> e;

        vector<vector<Edge>> graph(v);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < e; i++) {
            int u, vv, w;
            cin >> u >> vv >> w;

            graph[u].push_back({vv, w});
            graph[vv].push_back({u, w});
        }

        primMST(v, graph);
}

*/