class Solution {
public:
    int getPos(int x) {
        return x + 1000;
    }
    
    int findTargetSumWays(vector<int>& nums, int S) {
        int numsLen = nums.size();
        vector<int> resultCnt(2050, 0);
        resultCnt[getPos(0)] = 1;
        for (int i = 0; i < numsLen; i++) {
            vector<int> newCnt(2050, 0);
            for (int j = nums[i]; j < 2050; j++) {
                newCnt[j - nums[i]] += resultCnt[j];
            }
            for (int j = 0; j + nums[i] < 2050; j++) {
                newCnt[j + nums[i]] += resultCnt[j];
            }
            resultCnt = newCnt;
        }
        if (getPos(S) < 2050) {
            return resultCnt[getPos(S)];
        } else {
            return 0;
        }
    }
};