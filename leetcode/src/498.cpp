class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int m = matrix.size();
        if (m == 0) return result;
        int n = matrix[0].size();
        if (n == 0) return result;
        
        for (int i = 0; i < m + n - 1; i++) {
            if (i % 2) {
                for (int j = min(i, n - 1); j >= 0 && i - j < m; j--) {
                    result.push_back(matrix[i - j][j]);
                }
            } else {
                for (int j = min(i, m - 1); j >= 0 && i - j < n; j--) {
                    result.push_back(matrix[j][i - j]);
                }
            }
        }
        
        return result;
    }
};