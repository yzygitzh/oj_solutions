class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        if (n == 0) return 0;
        vector<int> minSum(triangle[n - 1].begin(), triangle[n - 1].end());
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                int sum1 = triangle[i][j] + minSum[j];
                int sum2 = triangle[i][j] + minSum[j + 1];
                minSum[j] = sum1 < sum2 ? sum1 : sum2;
            }
        }
        return minSum[0];
    }
};