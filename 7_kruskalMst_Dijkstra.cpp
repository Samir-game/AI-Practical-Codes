#include <bits/stdc++.h>
using namespace std;


// -------------------------------------------------
// Part 1: Kruskal's Minimum Spanning Tree
// -------------------------------------------------
struct Edge {
    int u, v, w;
};

bool compareEdge(Edge a, Edge b) {
    return a.w < b.w;
}

class DSU {
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

        if (rankArr[px] < rankArr[py])
            parent[px] = py;
        else if (rankArr[px] > rankArr[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rankArr[px]++;
        }
    }
};

void kruskal(int v, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdge);

    DSU dsu(v);
    int total = 0;

    cout << "\nEdges in MST:\n";

    for (auto e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            cout << e.u << " - " << e.v << " : " << e.w << endl;
            total += e.w;
        }
    }

    cout << "Total Cost = " << total << endl;
}

/*
Time Complexity
 O(E log E)
Space Complexity
 O(V)
Breaking Conditions
 Sorting bottleneck:
  E ≈ 10⁷ → sorting becomes slow
 Memory issue:
  Edge list fails at E ≈ 10⁸
 Disconnected graph:
  Only gives forest, not full MST
*/

// -------------------------------------------------
// Part 2: Dijkstra Shortest Path
// -------------------------------------------------
struct Node {
    int to, wt;
};

void dijkstra(int vertices, vector<vector<Node>>& graph, int start, int goal) {
    vector<int> dist(vertices, INT_MAX);
    vector<int> parent(vertices, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : graph[u]) {
            int v = edge.to;
            int w = edge.wt;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[goal] == INT_MAX) {
        cout << "\nNo path exists\n";
        return;
    }

    cout << "\nShortest Distance = " << dist[goal] << endl;


    vector<int> path;
    for (int v = goal; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int node : path)
        cout << node << " ";
    cout << endl;
}



int main() {
    int choice;

    cout << "Choose Algorithm:\n";
    cout << "1. Kruskal MST\n";
    cout << "2. Dijkstra Shortest Path\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int v, e;
        cout << "Enter number of vertices: ";
        cin >> v;

        cout << "Enter number of edges: ";
        cin >> e;

        vector<Edge> edges(e);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < e; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        kruskal(v, edges);
    }
    else if (choice == 2) {
        int V, E;
        cout << "Enter number of vertices: ";
        cin >> V;

        cout << "Enter number of edges: ";
        cin >> E;

        vector<vector<Node>> graph(V);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < E; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w}); 
        }

        int start, goal;
        cout << "Enter source vertex: ";
        cin >> start;
        cout << "Enter destination vertex: ";
        cin >> goal;

        dijkstra(V, graph, start, goal);
    }
    else {
        cout << "Invalid Choice";
    }

    return 0;
}

/*
====================================================
Dummy Input Test Case 1: Kruskal MST
====================================================

Enter choice: 1
Enter number of vertices: 4
Enter number of edges: 5

Enter edges (u v weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Expected Output:
Edges in MST:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10
Total Cost = 19


====================================================
Dummy Input Test Case 2: Dijkstra
====================================================

Enter choice: 2
Enter number of vertices: 5
Enter number of edges: 6

Enter edges (u v weight):
0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 4 1

Enter source vertex: 0

Expected Output:
Shortest Distance from Source 0:
To 0 = 0
To 1 = 2
To 2 = 3
To 3 = 7
To 4 = 6

====================================================
*/
