class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        // F[n][m]: minimum sum with first n nums and m arrays split
        // F[n][m] is mono, can binary search
        int numsLen = nums.size();
        
        vector<int> prefixSum(numsLen + 1);
        prefixSum[0] = 0;
        for (int i = 1; i <= numsLen; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
        }
        
        vector<vector<int>> minMaxSum(numsLen + 1, vector<int>(m + 1));
        for (int i = 1; i <= numsLen; i++) {
            minMaxSum[i][1] = prefixSum[i]; // split into single array
            for (int j = 2; j <= min(m, i); j++) {
                // numbers are split into j arrays
                // bin search in F[?][j - 1]
                int left = j - 1, right = i - 1;
                while (left + 1 < right) {
                    int mid = (left + right) / 2;
                    if (minMaxSum[mid][j - 1] < prefixSum[i] - prefixSum[mid]) {
                        left = mid;
                    } else {
                        right = mid;
                    }
                }
                int leftSum = max(minMaxSum[left][j - 1],
                                     prefixSum[i] - prefixSum[left]);
                int rightSum = max(minMaxSum[right][j - 1],
                                      prefixSum[i] - prefixSum[right]);
                minMaxSum[i][j] = min(leftSum, rightSum);
            }
        }
        return minMaxSum[numsLen][m];
    }
};