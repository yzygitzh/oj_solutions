class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        // use bfs
        
        int m = rooms.size();
        if (m == 0) return;
        int n = rooms[0].size();
        if (n == 0) return;
        
        queue<vector<int>> bfsQ;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    visited[i][j] = 1;
                    bfsQ.push(vector<int>{i, j, 0});
                }
            }
        }
                    
        while (!bfsQ.empty()) {
            vector<int> pos = bfsQ.front();
            bfsQ.pop();
            rooms[pos[0]][pos[1]] = pos[2];
            if (pos[0] - 1 >= 0 &&
                rooms[pos[0] - 1][pos[1]] > pos[2] + 1 &&
                !visited[pos[0] - 1][pos[1]]) {
                visited[pos[0] - 1][pos[1]] = 1;
                bfsQ.push(vector<int>{pos[0] - 1, pos[1], pos[2] + 1});
            }
            if (pos[0] + 1 < m &&
                rooms[pos[0] + 1][pos[1]] > pos[2] + 1 &&
                !visited[pos[0] + 1][pos[1]]) {
                visited[pos[0] + 1][pos[1]] = 1;
                bfsQ.push(vector<int>{pos[0] + 1, pos[1], pos[2] + 1});
            }
            if (pos[1] - 1 >= 0 &&
                rooms[pos[0]][pos[1] - 1] > pos[2] + 1 &&
                !visited[pos[0]][pos[1] - 1]) {
                visited[pos[0]][pos[1] - 1] = 1;
                bfsQ.push(vector<int>{pos[0], pos[1] - 1, pos[2] + 1});
            }
            if (pos[1] + 1 < n &&
                rooms[pos[0]][pos[1] + 1] > pos[2] + 1 &&
                !visited[pos[0]][pos[1] + 1]) {
                visited[pos[0]][pos[1] + 1] = 1;
                bfsQ.push(vector<int>{pos[0], pos[1] + 1, pos[2] + 1});
            }
        }
    }
};