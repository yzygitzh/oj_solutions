class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        // use binary search of prefix sums
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        long long maxVal = (long long)(int)(1L << 31);
        
        for (int i = 0; i < m; i++) {
            vector<long long> preSum(n + 1, 0), normalSum(n, 0);
            for (int j = i; j < m; j++) {
                for (int p = 0; p < n; p++) {
                    normalSum[p] += matrix[j][p];
                }
                set<long long> preSums{0};
                for (int p = 0; p < n; p++) {
                    preSum[p + 1] = preSum[p] + normalSum[p];
                    // preSum1 >= preSum2 - k
                    auto itr = preSums.lower_bound(preSum[p + 1] -
                                                   (long long)k);
                    if (itr != preSums.end()) {
                        long long currVal = preSum[p + 1] - (*itr);
                        // if (i == 0 && j == 0 && p == 2) return currVal > maxVal;
                        if (currVal > maxVal &&
                            currVal <= (long long)k) maxVal = currVal;
                    }
                    preSums.insert(preSum[p + 1]);
                }
            }
        }
        
        return (int)maxVal;
    }
};