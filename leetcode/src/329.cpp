class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        if (n == 0) return 0;
        
        vector<vector<int>> memo(m, vector<int>(n, -1));
        int maxLen = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dfs(i, j, matrix, memo);
                if (memo[i][j] > maxLen) maxLen = memo[i][j];
            }
        }
        return maxLen;
    }
    
    int dfs(int row, int col, vector<vector<int>>& matrix, vector<vector<int>>& memo) {
        if (memo[row][col] == -1) {
            int m = matrix.size();
            int n = matrix[0].size();
            
            int maxLen = 1;
            if (row - 1 >= 0 && matrix[row - 1][col] > matrix[row][col]) {
                int currLen = 1 + dfs(row - 1, col, matrix, memo);
                if (currLen > maxLen) maxLen = currLen;
            }
            if (row + 1 < m && matrix[row + 1][col] > matrix[row][col]) {
                int currLen = 1 + dfs(row + 1, col, matrix, memo);
                if (currLen > maxLen) maxLen = currLen;
            }
            if (col - 1 >= 0 && matrix[row][col - 1] > matrix[row][col]) {
                int currLen = 1 + dfs(row, col - 1, matrix, memo);
                if (currLen > maxLen) maxLen = currLen;
            }
            if (col + 1 < n && matrix[row][col + 1] > matrix[row][col]) {
                int currLen = 1 + dfs(row, col + 1, matrix, memo);
                if (currLen > maxLen) maxLen = currLen;
            }
            
            memo[row][col] = maxLen;
        }
        return memo[row][col];
    }
};