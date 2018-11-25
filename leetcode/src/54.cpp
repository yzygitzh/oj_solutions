class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int m = matrix.size();
        if (m == 0) return result;
        int n = matrix[0].size();
        if (n == 0) return result;
        
        int smallEdge = m < n ? m : n;
        
        for (int i = 0; i * 2 + 1 < smallEdge; i++) {
            // up edge
            for (int j = i; j < n - i - 1; j++) {
                result.push_back(matrix[i][j]);
            }
            // right edge
            for (int j = i; j < m - i - 1; j++) {
                result.push_back(matrix[j][n - i - 1]);
            }
            // down edge
            for (int j = n - i - 1; j > i; j--) {
                result.push_back(matrix[m - i - 1][j]);
            }
            // left edge
            for (int j = m - i - 1; j > i; j--) {
                result.push_back(matrix[j][i]);
            }
        }
        
        int restLen = m * n - result.size();
        if (restLen > 0) {
            if (m > n) {
                for (int i = 0; i < restLen; i++) {
                    result.push_back(matrix[n / 2 + i][n / 2]);
                }
            } else {
                for (int i = 0; i < restLen; i++) {
                    result.push_back(matrix[m / 2][m / 2 + i]);
                }
            }
        }
        
        return result;
    }
};