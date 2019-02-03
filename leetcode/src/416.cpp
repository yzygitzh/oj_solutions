class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 0/1 knapsack
        // F[N][M]: M can be summed to using first N elements
        // F[N][M] = F[N-1][M-val(N)] || F[N-1][M]
        int numsLen = nums.size();
        if (numsLen <= 1) return false;
        int numsSum = 0;
        for (int i = 0; i < numsLen; i++) {
            numsSum += nums[i];
        }
        if (numsSum % 2) return false;
        vector<vector<int>> F(2, vector<int>(numsSum / 2 + 1, 0));
        F[0][0] = 1;
        for (int i = 1; i <= numsLen; i++) {
            for (int j = 0; j <= numsSum / 2; j++) {
                F[i % 2][j] = F[(i - 1) % 2][j];
                if (j - nums[i - 1] >= 0) {
                    F[i % 2][j] |= F[(i - 1) % 2][j - nums[i - 1]];
                }
            }
        }
        return F[numsLen % 2][numsSum / 2];
    }
};