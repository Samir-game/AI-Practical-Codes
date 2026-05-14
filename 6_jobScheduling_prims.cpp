#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

/*
====================================================
Program Implements:
1. Job Scheduling Problem
2. Prim's Minimum Spanning Tree Algorithm
====================================================
*/

// -------------------------------------------------
// Part 1: Job Scheduling Problem (Greedy)
// -------------------------------------------------
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

    cout << "\nSelected Jobs:\n";
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-')
            cout << slot[i] << " ";
    }

    cout << "\nTotal Profit = " << totalProfit << endl;
}

// -------------------------------------------------
// Part 2: Prim's Minimum Spanning Tree
// ------------------------------------------------
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

// -------------------------------------------------
// Main Function
// -------------------------------------------------
int main() {
    int choice;

    cout << "Choose Operation:\n";
    cout << "1. Job Scheduling Problem\n";
    cout << "2. Prim's Minimum Spanning Tree\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
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

    else if (choice == 2) {
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

    else {
        cout << "Invalid Choice";
    }

    return 0;
}

/*
====================================================
Dummy Input Test Case 1: Job Scheduling Problem
====================================================

Enter choice: 1
Enter number of jobs: 5

Enter job details (id deadline profit):
A 2 100
B 1 19
C 2 27
D 1 25
E 3 15

Expected Output:
Selected Jobs:
C A E
Total Profit = 142


====================================================
Dummy Input Test Case 2: Prim's Minimum Spanning Tree
====================================================

Enter choice: 2
Enter number of vertices: 5
Enter number of edges: 7

Enter edges (u v weight):
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9

Expected Output:
Edges in Prim's MST:
0 - 1 : 2
1 - 2 : 3
0 - 3 : 6
1 - 4 : 5
Total Cost = 16

Time Complexity
 O((V + E) log V)
Space Complexity
 O(V)
Breaking Conditions
 Disconnected graph:
  Output is incomplete MST
 Dense graph issue:
  When V > 10⁴, E ≈ 10⁸ → memory/time problem

====================================================
*/