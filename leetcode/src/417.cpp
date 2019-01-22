class Solution {
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> result;
        
        int m = matrix.size();
        if (m == 0) return result;
        int n = matrix[0].size();
        if (n == 0) return result;
        
        vector<vector<int>> target(m, vector<int>(n, 0));
        vector targetVal{0x1, 0x2};
        
        for (auto itr = targetVal.begin(); itr != targetVal.end(); ++itr) {
            // bfs left-up and right-down edges
            queue<pair<int, int>> bfsQ;
            vector<vector<int>> visited(m, vector<int>(n, 0));
        
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (*itr == 0x1 && (i == 0 || j == 0) ||
                        *itr == 0x2 && (i == m - 1 || j == n - 1)) {
                        bfsQ.push(make_pair(i, j));
                        visited[i][j] = 1;
                    }
                }
            }
            while (!bfsQ.empty()) {
                pair<int, int> top = bfsQ.front();
                bfsQ.pop();
                int row = top.first, col = top.second;
                target[row][col] |= *itr;
                if (row - 1 >= 0 && !visited[row - 1][col] &&
                    matrix[row - 1][col] >= matrix[row][col]) {
                    visited[row - 1][col] = 1;
                    bfsQ.push(make_pair(row - 1, col));
                }
                if (row + 1 < m && !visited[row + 1][col] &&
                    matrix[row + 1][col] >= matrix[row][col]) {
                    visited[row + 1][col] = 1;
                    bfsQ.push(make_pair(row + 1, col));
                }
                if (col - 1 >= 0 && !visited[row][col - 1] &&
                    matrix[row][col - 1] >= matrix[row][col]) {
                    visited[row][col - 1] = 1;
                    bfsQ.push(make_pair(row, col - 1));
                }
                if (col + 1 < n && !visited[row][col + 1] &&
                    matrix[row][col + 1] >= matrix[row][col]) {
                    visited[row][col + 1] = 1;
                    bfsQ.push(make_pair(row, col + 1));
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (target[i][j] == 0x3) {
                    result.push_back(make_pair(i, j));
                }
            }
        }
        
        return result;
    }
};