class Solution {
public:
    int m, n;
    
    pair<int, int> dirToRC(int row, int col, int dir) {
        if (dir == 0x1) return make_pair(row - 1, col);
        else if (dir == 0x2) return make_pair(row + 1, col);
        else if (dir == 0x4) return make_pair(row, col - 1);
        else return make_pair(row, col + 1);
    }
    
    bool validRC(int row, int col) {
        return row >= 0 && row < m && col >= 0 && col < n;
    }
    
    bool hasPath(vector<vector<int>>& maze,
                 vector<int>& start, vector<int>& destination) {
        m = maze.size();
        if (m == 0) return false;
        n = maze[0].size();
        if (n == 0) return false;
        
        vector<vector<int>> visited(m, vector<int>(n, 0));
        // row, col, direction
        queue<vector<int>> bfsQ;
        for (int i = 0; i < 4; i++) {
            bfsQ.push(vector<int>{start[0], start[1], (1 << i)});
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (maze[i][j] == 1) visited[i][j] = 0xF;
            }
        }
        
        while (!bfsQ.empty()) {
            vector<int> currState = bfsQ.front();
            bfsQ.pop();
            int row = currState[0], col = currState[1], dir = currState[2];
            // first try origin direction
            pair<int, int> newPos = dirToRC(row, col, dir);
            if (validRC(newPos.first, newPos.second) &&
                !(visited[newPos.first][newPos.second] & dir)) {
                visited[newPos.first][newPos.second] |= dir;
                bfsQ.push(vector<int>{newPos.first, newPos.second, dir});
            } else {
                // stopped, try other directions
                for (int i = 0; i < 4; i++) {
                    int newDir = (1 << i);
                    if (newDir == dir) continue;
                    newPos = dirToRC(row, col, newDir);
                    if (validRC(newPos.first, newPos.second) &&
                        !(visited[newPos.first][newPos.second] & newDir)) {
                        visited[newPos.first][newPos.second] |= newDir;
                        bfsQ.push(vector<int>{newPos.first, newPos.second, newDir});
                    }
                }
            }
        }
        bool canStop = false;
        for (int i = 0; i < 4; i++) {
            int dir = (1 << i);
            pair<int, int> newPos = dirToRC(destination[0], destination[1], dir);
            if ((visited[destination[0]][destination[1]] & dir) &&
                (!validRC(newPos.first, newPos.second) ||
                 maze[newPos.first][newPos.second] == 1)) {
                canStop = true;
                break;
            }
        }
        return canStop;
    }
};