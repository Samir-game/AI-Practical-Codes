#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class GraphTree {
private:
    int vertices;
    vector<vector<int>> adj;
    vector<bool> visited;

public:
    GraphTree(int v) {
        vertices = v;
        adj.resize(v);
        visited.resize(v, false);
    }

    // Add edge (Undirected)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Reset visited array
    void resetVisited() {
        fill(visited.begin(), visited.end(), false);
    }

    // ---------------- DFS (Recursive) ----------------
    void DFS(int node) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                DFS(neighbor);
            }
        }
    }

    // DFS for disconnected graph
    void DFS_All() {
        resetVisited();
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                DFS(i);
            }
        }
    }

    // ---------------- BFS ----------------
    void BFS(int start) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // BFS for disconnected graph
    void BFS_All() {
        resetVisited();
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                BFS(i);
            }
        }
    }
};

int main() {
    int v, e, choice;

    cout << "Choose Structure:\n";
    cout << "1. Graph\n";
    cout << "2. Tree\n";
    cout << "Enter choice: ";
    cin >> choice;

    cout << "Enter number of vertices: ";
    cin >> v;

    GraphTree gt(v);

    if (choice == 1) {
        cout << "Enter number of edges: ";
        cin >> e;
        cout << "Enter edges (u v):\n";

        for (int i = 0; i < e; i++) {
            int u, w;
            cin >> u >> w;
            gt.addEdge(u, w);
        }
    }
    else if (choice == 2) {
        cout << "For Tree, enter " << v - 1 << " edges:\n";

        for (int i = 0; i < v - 1; i++) {
            int u, w;
            cin >> u >> w;
            gt.addEdge(u, w);
        }
    }
    else {
        cout << "Invalid Choice\n";
        return 0;
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

 

    // ---------- DFS ----------
    cout << "\nDFS Traversal (from start): ";
    gt.resetVisited();
    gt.DFS(start);

    cout << "\nDFS Traversal (complete graph): ";
    gt.DFS_All();

    // ---------- BFS ----------
    cout << "\nBFS Traversal (from start): ";
    gt.resetVisited();
    gt.BFS(start);

    cout << "\nBFS Traversal (complete graph): ";
    gt.BFS_All();

    return 0;
}

/*

Enter choice: 1
Enter number of vertices: 5
Enter number of edges: 5
Enter edges (u v):
0 1
0 2
1 3
1 4
2 4
Enter starting vertex: 0
    0
   / \
  1   2
 / \   \
3   4--- 
DFS Traversal (from start): 0 1 3 4 2
DFS Traversal (complete graph): 0 1 3 4 2
BFS Traversal (from start): 0 1 2 3 4
BFS Traversal (complete graph): 0 1 2 3 4

Enter choice: 2
Enter number of vertices: 6
For Tree, enter 5 edges:
0 1
0 2
1 3
1 4
2 5
Enter starting vertex: 0
        0
       / \
      1   2
     / \   \
    3   4   5

DFS Traversal (from start): 0 1 3 4 2 5
DFS Traversal (complete graph): 0 1 3 4 2 5
BFS Traversal (from start): 0 1 2 3 4 5
BFS Traversal (complete graph): 0 1 2 3 4 5
*/