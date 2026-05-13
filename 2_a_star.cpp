#include <bits/stdc++.h> 

using namespace std;

struct Node {
    int x, y;       
    int g, h, f;   

    Node(int x, int y, int g, int h) {
        this->x = x;
        this->y = y;
        this->g = g;
        this->h = h;
        this->f = g + h;
    }
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.f > b.f;
    }
};


bool isValid(int x, int y, int n, int m, vector<vector<int>>& grid) {
    return (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 0);
}


int heuristic(int x, int y, int goalX, int goalY) {
    return abs(x - goalX) + abs(y - goalY);
}


void aStar(vector<vector<int>>& grid, int startX, int startY, int goalX, int goalY) {
    int n = grid.size();
    int m = grid[0].size();

    priority_queue<Node, vector<Node>, Compare> pq;

    vector<vector<bool>> visited(n, vector<bool>(m, false));


    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1, -1}));

    pq.push(Node(startX, startY, 0, heuristic(startX, startY, goalX, goalY)));

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1}; 

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int x = current.x;
        int y = current.y;

        if (visited[x][y]) continue;
        visited[x][y] = true;

       
        if (x == goalX && y == goalY) {
            cout << "\nGoal Reached!\nPath: ";

            vector<pair<int,int>> path;
            int cx = goalX, cy = goalY;

            while (cx != -1 && cy != -1) {
                path.push_back({cx, cy});
                auto p = parent[cx][cy];
                cx = p.first;
                cy = p.second;
            }

            reverse(path.begin(), path.end());

            for (auto &p : path) {
                cout << "(" << p.first << "," << p.second << ") ";
            }

            cout << endl;
            return;
        }

    
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY, n, m, grid) && !visited[newX][newY]) {
                int newG = current.g + 1;
                int newH = heuristic(newX, newY, goalX, goalY);

                parent[newX][newY] = {x, y};   
                pq.push(Node(newX, newY, newG, newH));
            }
        }
    }

    cout << "\nNo Path Found!" << endl;
}

int main() {
    int n, m;
    cout << "Enter rows and columns of grid: ";
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    cout << "Enter grid values (0 = free path, 1 = obstacle):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int sx, sy, gx, gy;
    cout << "Enter start position (x y): ";
    cin >> sx >> sy;

    cout << "Enter goal position (x y): ";
    cin >> gx >> gy;

    cout << "\nA* Shortest Path:\n";
    aStar(grid, sx, sy, gx, gy);

    return 0;
}

/*
Enter rows and columns of grid: 5 5

Enter grid:
0 0 0 1 0
1 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 0 0

Enter start position: 0 0
Enter goal position: 4 4

Expected Output:
A* Search Path:
(0,0) (0,1) (0,2) (1,2) (2,2) (2,3) (2,4) (3,4) (4,4)
Goal Reached!

====================================================


Time Complexity
Worst: O(E)
Practical: depends on heuristic
Space Complexity
O(V)
Breaking Conditions
Memory failure:
-->Open + closed list → fails around 10⁶ nodes
Bad heuristic:
-->If heuristic overestimates → incorrect result
Performance collapse:
-->If heuristic = 0 → becomes Dijkstra
-->Slow when branching factor high (b ≥ 10, depth ≥ 10 → 10¹⁰ states)
*/
