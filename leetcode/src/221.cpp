class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        if (n == 0) return 0;

        vector<vector<int> > maxSqr(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            maxSqr[i][0] = matrix[i][0] == '1' ? 1 : 0;
        }
        for (int i = 0; i < n; i++) {
            maxSqr[0][i] = matrix[0][i] == '1' ? 1 : 0;
        }

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '0') {
                    maxSqr[i][j] = 0;
                } else {
                    int minLen = maxSqr[i - 1][j - 1];
                    if (maxSqr[i - 1][j] < minLen) minLen = maxSqr[i - 1][j];
                    if (maxSqr[i][j - 1] < minLen) minLen = maxSqr[i][j - 1];
                    maxSqr[i][j] = minLen + 1;
                }
            }
        }

        int maxLen = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (maxSqr[i][j] > maxLen) maxLen = maxSqr[i][j];
            }
        }
        
        return maxLen * maxLen;
    }
};