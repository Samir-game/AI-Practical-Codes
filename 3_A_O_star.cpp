#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

struct Node {
    string name;
    int heuristic;
    bool solved;
    vector<vector<int>> children; 
};

vector<Node> graph;

// AO* Recursive Function
int AOStar(int current) {
    if (graph[current].children.empty()) {
        graph[current].solved = true;
        return 0;
    }

    int minCost = INT_MAX;

    for (auto option : graph[current].children) {
        int cost = 0;

        for (int child : option) {
            cost += graph[child].heuristic + AOStar(child);
        }

        if (cost < minCost) {
            minCost = cost;
        }
    }

    graph[current].heuristic = minCost;
    graph[current].solved = true;

    return minCost;
}

int main() {
    int n;
    cout << "Enter number of game states (nodes): ";
    cin >> n;

    graph.resize(n);

    // Input node names and heuristic
    for (int i = 0; i < n; i++) {
        cout << "Enter node name and heuristic for node " << i << ": ";
        cin >> graph[i].name >> graph[i].heuristic;
        graph[i].solved = false;
    }

    int goal;
    cout << "Enter goal node index: ";
    cin >> goal;
    graph[goal].solved = true;

    // Input graph structure
    for (int i = 0; i < n; i++) {
        if (i == goal) continue;

        int groups;
        cout << "\nEnter number of options for node " << graph[i].name << ": ";
        cin >> groups;

        for (int g = 0; g < groups; g++) {
            int k;
            cout << "Enter number of child nodes in option " << g + 1 << ": ";
            cin >> k;

            vector<int> option;
            cout << "Enter child node indices: ";
            for (int j = 0; j < k; j++) {
                int child;
                cin >> child;
                option.push_back(child);
            }

            graph[i].children.push_back(option);
        }
    }

    int start;
    cout << "\nEnter start node index: ";
    cin >> start;

    int result = AOStar(start);

    cout << "\nOptimal Cost from Start Node = " << result << endl;
    cout << "Updated Heuristic of Start Node = " << graph[start].heuristic << endl;

    return 0;
}

/*
==================================================
About the Game: Treasure Hunt Decision Game
==================================================

Each node = a game state / location.
Goal = reach treasure with minimum cost.

Rules:
1. OR Option:
   Choose one path only.

2. AND Option:
   Complete all child paths.

AO* searches all possibilities and gives best path.

Example:
A -> B OR C
B -> D AND E
C -> F
D -> G
E -> G
F -> G

Goal = G

==================================================
Dummy Input:
==================================================

Enter number of game states (nodes): 7

Enter node name and heuristic for node 0: A 10
Enter node name and heuristic for node 1: B 6
Enter node name and heuristic for node 2: C 4
Enter node name and heuristic for node 3: D 2
Enter node name and heuristic for node 4: E 2
Enter node name and heuristic for node 5: F 3
Enter node name and heuristic for node 6: G 0

Enter goal node index: 6

Enter number of options for node A: 2
Enter number of child nodes in option 1: 1
Enter child node indices: 1
Enter number of child nodes in option 2: 1
Enter child node indices: 2

Enter number of options for node B: 1
Enter number of child nodes in option 1: 2
Enter child node indices: 3 4

Enter number of options for node C: 1
Enter number of child nodes in option 1: 1
Enter child node indices: 5

Enter number of options for node D: 1
Enter number of child nodes in option 1: 1
Enter child node indices: 6

Enter number of options for node E: 1
Enter number of child nodes in option 1: 1
Enter child node indices: 6

Enter number of options for node F: 1
Enter number of child nodes in option 1: 1
Enter child node indices: 6

Enter start node index: 0

==================================================
Expected Output:
==================================================

Optimal Cost from Start Node = 4
Updated Heuristic of Start Node = 4

==================================================

Time Complexity
 Worst: O(b^d) (exponential)
Space Complexity
 O(N)
Breaking Conditions
 State explosion:
  Breaks when nodes ≈ 10⁵–10⁶
 Cycles in graph:
  Without proper handling → infinite loop
 Memory overflow:
  AND-OR graph grows too large
*/