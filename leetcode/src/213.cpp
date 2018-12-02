class Solution {
public:
    int rob(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        if (numsLen == 1) return nums[0];
        
        int maxRob = 0;
        
        // for each skipIdx, calc maximum robber
        // note that all cases can be divided into
        // i-th is not robbed and (i+1)-th is not robbed
        // because they cannot be both robbed!
        
        for (int skipIdx = 0; skipIdx < 2; skipIdx++) {
            // robSum[i]: max rob when robbing first i+1 houses
            vector<int> robSum(numsLen - 1, 0);
            robSum[1] = robSum[0] = nums[(0 + skipIdx) % numsLen];
            if (nums[(1 + skipIdx) % numsLen] > robSum[1]) {
                robSum[1] = nums[(1 + skipIdx) % numsLen];
            }
            for (int i = 2; i <= numsLen - 2; i++) {
                robSum[i] = robSum[i - 1];
                if (robSum[i - 2] + nums[(i + skipIdx) % numsLen] > robSum[i]) {
                    robSum[i] = robSum[i - 2] + nums[(i + skipIdx) % numsLen];
                }
            }
            for (int i = 0; i <= numsLen - 2; i++) {
                if (robSum[i] > maxRob) maxRob = robSum[i];
            }
        }
        
        return maxRob;
    }
};