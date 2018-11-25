class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        if (n == 0) return 0;
        
        vector<vector<int> > pathSum(m, vector<int>(n, 0));
        pathSum[0][0] = grid[0][0];

        int sum;
        sum = pathSum[0][0];
        for (int i = 1; i < m; i++) {
            sum += grid[i][0];
            pathSum[i][0] = sum;
        }
        
        sum = pathSum[0][0];
        for (int i = 1; i < n; i++) {
            sum += grid[0][i];
            pathSum[0][i] = sum;
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                int sum1 = pathSum[i - 1][j] + grid[i][j];
                int sum2 = pathSum[i][j - 1] + grid[i][j];
                pathSum[i][j] = sum1 < sum2 ? sum1 : sum2;
            }
        }
        
        return pathSum[m - 1][n - 1];
    }
};