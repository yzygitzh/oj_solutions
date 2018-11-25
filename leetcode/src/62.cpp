class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0) return 0;
        vector<vector<int> > pathNum(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            pathNum[i][0] = 1;
        }
        for (int i = 0; i < n; i++) {
            pathNum[0][i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                pathNum[i][j] = pathNum[i - 1][j] + pathNum[i][j - 1];
            }
        }
        return pathNum[m - 1][n - 1];
    }
};