#include <bits/stdc++.h>
using namespace std;

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


struct Job {
    char id;
    int deadline;
    int profit;
};

bool compareJob(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compareJob);

    int maxDeadline = 0;
    for (auto job : jobs)
        maxDeadline = max(maxDeadline, job.deadline);

    vector<char> slot(maxDeadline + 1, '-');
    int totalProfit = 0;

    for (auto job : jobs) {
        for (int j = job.deadline; j >= 1; j--) {
            if (slot[j] == '-') {
                slot[j] = job.id;
                totalProfit += job.profit;
                break;
            }
        }
    }

    cout << "\nSelected Jobs: ";
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-')
            cout << slot[i] << " ";
    }

    cout << "\nTotal Profit = " << totalProfit << endl;
}

int main() {
    int choice;

    cout << "Choose Operation:\n";
    cout << "1. Single Source Shortest Path\n";
    cout << "2. Job Scheduling Problem\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
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

    else if (choice == 2) {
        int n;
        cout << "Enter number of jobs: ";
        cin >> n;

        vector<Job> jobs(n);

        cout << "Enter job details (id deadline profit):\n";
        for (int i = 0; i < n; i++) {
            cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
        }

        jobScheduling(jobs);
    }

    else {
        cout << "Invalid Choice\n";
    }

    return 0;
}
