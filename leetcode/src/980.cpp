class Solution {
public:
    int pathCnt = 0;
    int maxLen = 0;
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n, 0));
        // vector<vector<int>> memo(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == -1) {
                    visited[i][j] = 1;
                }
                if (grid[i][j] == 0) {
                    maxLen++;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j, visited, 0);
                }
            }
        }
        return pathCnt;
    }
    
    void dfs(vector<vector<int>>& grid, int row, int col,
             vector<vector<int>>& visited, int len) {
        if (grid[row][col] == 2 && len == maxLen + 1) {
            pathCnt++;
        } else {
            visited[row][col] = 1;
            
            int m = grid.size();
            int n = grid[0].size();
            if (row - 1 >= 0 && !visited[row - 1][col]) {
                dfs(grid, row - 1, col, visited, len + 1);
            }
            if (row + 1 < m && !visited[row + 1][col]) {
                dfs(grid, row + 1, col, visited, len + 1);
            }
            if (col - 1 >= 0 && !visited[row][col - 1]) {
                dfs(grid, row, col - 1, visited, len + 1);
            }
            if (col + 1 < n && !visited[row][col + 1]) {
                dfs(grid, row, col + 1, visited, len + 1);
            }

            visited[row][col] = 0;
        }
        
    }
};