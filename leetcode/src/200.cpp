class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        if (n == 0) return 0;
        
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    dfs(i, j, grid);
                    count++;
                }
            }
        }
        
        return count;
    }
    
    void dfs(int row, int col,
             vector<vector<char> > &grid) {
        grid[row][col] = 'x';
        if (row - 1 >= 0 && grid[row - 1][col] == '1') {
            dfs(row - 1, col, grid);
        }
        if (row + 1 < grid.size() && grid[row + 1][col] == '1') {
            dfs(row + 1, col, grid);
        }
        if (col - 1 >= 0 && grid[row][col - 1] == '1') {
            dfs(row, col - 1, grid);
        }
        if (col + 1 < grid[0].size() && grid[row][col + 1] == '1') {
            dfs(row, col + 1, grid);
        }
    }
};