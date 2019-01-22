class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        int maxSum = nums[0], maxCurr = maxSum;
        for (int i = 1; i < numsLen; i++) {
            maxCurr = max(maxCurr + nums[i], nums[i]);
            maxSum = max(maxSum, maxCurr);
        }
        return maxSum;
    }
};