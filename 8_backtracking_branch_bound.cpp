#include <iostream>
#include <vector>
using namespace std;

/*
====================================================
Program Implements Constraint Satisfaction Problems:
1. N-Queens using Backtracking
2. Graph Coloring using Branch and Bound
====================================================
*/

// -------------------------------------------------
// Part 1: N-Queens using Backtracking
// -------------------------------------------------
bool isSafeQueen(vector<vector<int>>& board, int row, int col, int n) {
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    for (int i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j]) return false;

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int col, int n) {
    if (col == n)
        return true;

    for (int i = 0; i < n; i++) {
        if (isSafeQueen(board, i, col, n)) {
            board[i][col] = 1;

            if (solveNQueens(board, col + 1, n))
                return true;

            board[i][col] = 0; // backtrack
        }
    }

    return false;
}

void printBoard(vector<vector<int>>& board, int n) {
    cout << "\nN-Queens Solution:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
}
/*
Time Complexity
 O(N!)
Space Complexity
 O(N)
Breaking Conditions
 Practical limit:
  Works fast till N ≤ 12
  Slow at N = 13–15
  Almost infeasible at N ≥ 16–20
 Recursion depth:
  Depth = N → safe up to ~10⁴ but time fails earlier
*/
// -------------------------------------------------
// Part 2: Graph Coloring using Branch and Bound
// -------------------------------------------------
bool isSafeColor(int node, vector<vector<int>>& graph,
                 vector<int>& color, int c, int v) {
    for (int i = 0; i < v; i++) {
        if (graph[node][i] && color[i] == c)
            return false;
    }
    return true;
}

bool graphColoringUtil(vector<vector<int>>& graph,
                       int m, vector<int>& color,
                       int node, int v) {
    if (node == v)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafeColor(node, graph, color, c, v)) {
            color[node] = c;

            if (graphColoringUtil(graph, m, color, node + 1, v))
                return true;

            color[node] = 0; // backtrack
        }
    }

    return false;
}

void graphColoring(vector<vector<int>>& graph, int v, int m) {
    vector<int> color(v, 0);

    if (graphColoringUtil(graph, m, color, 0, v)) {
        cout << "\nGraph Coloring Solution:\n";
        for (int i = 0; i < v; i++) {
            cout << "Vertex " << i << " -> Color " << color[i] << endl;
        }
    } else {
        cout << "\nNo solution exists with " << m << " colors.\n";
    }
}


int main() {
    int choice;

    cout << "Choose Problem:\n";
    cout << "1. N-Queens Problem\n";
    cout << "2. Graph Coloring Problem\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int n;
        cout << "Enter value of N: ";
        cin >> n;

        vector<vector<int>> board(n, vector<int>(n, 0));

        if (solveNQueens(board, 0, n))
            printBoard(board, n);
        else
            cout << "No solution exists.\n";
    }

    else if (choice == 2) {
        int v, m;
        cout << "Enter number of vertices: ";
        cin >> v;

        vector<vector<int>> graph(v, vector<int>(v));

        cout << "Enter adjacency matrix:\n";
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                cin >> graph[i][j];

        cout << "Enter number of colors: ";
        cin >> m;

        graphColoring(graph, v, m);
    }

    else {
        cout << "Invalid Choice";
    }

    return 0;
}

/*
====================================================
Dummy Input Test Case 1: N-Queens
====================================================

Enter choice: 1
Enter value of N: 4

Expected Output:
N-Queens Solution:
. . Q .
Q . . .
. . . Q
. Q . .


====================================================
Dummy Input Test Case 2: Graph Coloring
====================================================

Enter choice: 2
Enter number of vertices: 4

Enter adjacency matrix:
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0

Enter number of colors: 3

Expected Output:
Graph Coloring Solution:
Vertex 0 -> Color 1
Vertex 1 -> Color 2
Vertex 2 -> Color 3
Vertex 3 -> Color 2

====================================================
*/