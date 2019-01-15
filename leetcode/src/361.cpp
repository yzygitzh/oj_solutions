class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        if (n == 0) return 0;
        
        vector<vector<int>> maxRow(m, vector<int>(n, 0));
        vector<vector<int>> maxCol(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            int currVal;
            currVal = 0;
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'W') currVal = 0;
                else if (grid[i][j] == 'E') currVal += 1;
                maxRow[i][j] += currVal;
            }
            currVal = 0;
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 'W') currVal = 0;
                else if (grid[i][j] == 'E') currVal += 1;
                maxRow[i][j] += currVal;
            }
        }

        for (int i = 0; i < n; i++) {
            int currVal;
            currVal = 0;
            for (int j = 0; j < m; j++) {
                if (grid[j][i] == 'W') currVal = 0;
                else if (grid[j][i] == 'E') currVal += 1;
                maxCol[j][i] += currVal;
            }
            currVal = 0;
            for (int j = m - 1; j >= 0; j--) {
                if (grid[j][i] == 'W') currVal = 0;
                else if (grid[j][i] == 'E') currVal += 1;
                maxCol[j][i] += currVal;
            }
        }

        int maxVal = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxVal = max((grid[i][j] == '0' ?
                              maxRow[i][j] + maxCol[i][j] : 0), maxVal);
            }
        }
        return maxVal;
    }
};