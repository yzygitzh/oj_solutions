class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        // BFS on all buildings
        int m = grid.size();
        if (m == 0) return -1;
        int n = grid[0].size();
        if (n == 0) return -1;
        
        vector<vector<int>> dis(m, vector<int>(n, 0));
        vector<vector<int>> count(m, vector<int>(n, 0));
        int buildCnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    buildCnt++;
                    vector<vector<int>> visited(m, vector<int>(n, 0));
                    queue<vector<int>> bfsQ;
                    bfsQ.push(vector<int>{i, j, 0});
                    visited[i][j] = 1;
                    while (!bfsQ.empty()) {
                        auto pos = bfsQ.front();
                        bfsQ.pop();
                        dis[pos[0]][pos[1]] += pos[2];
                        count[pos[0]][pos[1]]++;
                        if (pos[0] - 1 >= 0 && !visited[pos[0] - 1][pos[1]] &&
                            grid[pos[0] - 1][pos[1]] == 0) {
                            visited[pos[0] - 1][pos[1]] = 1;
                            bfsQ.push(vector<int>{pos[0] - 1, pos[1], pos[2] + 1});
                        }
                        if (pos[0] + 1 < m && !visited[pos[0] + 1][pos[1]] &&
                            grid[pos[0] + 1][pos[1]] == 0) {
                            visited[pos[0] + 1][pos[1]] = 1;
                            bfsQ.push(vector<int>{pos[0] + 1, pos[1], pos[2] + 1});
                        }
                        if (pos[1] - 1 >= 0 && !visited[pos[0]][pos[1] - 1] &&
                            grid[pos[0]][pos[1] - 1] == 0) {
                            visited[pos[0]][pos[1] - 1] = 1;
                            bfsQ.push(vector<int>{pos[0], pos[1] - 1, pos[2] + 1});
                        }
                        if (pos[1] + 1 < n && !visited[pos[0]][pos[1] + 1] &&
                            grid[pos[0]][pos[1] + 1] == 0) {
                            visited[pos[0]][pos[1] + 1] = 1;
                            bfsQ.push(vector<int>{pos[0], pos[1] + 1, pos[2] + 1});
                        }
                    }
                }
            }
        }
        
        bool found = false;
        int minDis = -1;
        if (buildCnt == 0) return minDis;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && count[i][j] == buildCnt) {
                    if (!found) {
                        found = true;
                        minDis = dis[i][j];
                    } else {
                        minDis = min(dis[i][j], minDis);
                    }
                }
            }
        }
        return minDis;
    }
};