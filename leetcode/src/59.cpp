class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int> > result(n, vector<int>(n, 0));
        
        int currNum = 1;
        for (int i = 0; i * 2 + 1 < n; i++) {
            // up edge
            for (int j = i; j < n - i - 1; j++) {
                result[i][j] = currNum++;
            }
            // right edge
            for (int j = i; j < n - i - 1; j++) {
                result[j][n - i - 1] = currNum++;
            }
            // down edge
            for (int j = n - i - 1; j > i; j--) {
                result[n - i - 1][j] = currNum++;
            }
            // left edge
            for (int j = n - i - 1; j > i; j--) {
                result[j][i] = currNum++;
            }
        }
        
        if (n % 2) result[n / 2][n / 2] = currNum;
        return result;
    }
};