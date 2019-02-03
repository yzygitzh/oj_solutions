class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int numsLen = nums.size();
        int result = 0;
        int oneCnt[32] = {0}, zeroCnt[32] = {0};
        for (int i = 0; i + 1 < numsLen; i++) {
            // add nums[i]
            unsigned uNum = (unsigned)nums[i];
            for (int j = 0; j < 32; j++) {
                if (uNum & 1) oneCnt[j]++;
                else zeroCnt[j]++;
                uNum >>= 1;
            }
            // update result
            uNum = (unsigned)nums[i + 1];
            for (int j = 0; j < 32; j++) {
                if (uNum & 1) result += zeroCnt[j];
                else result += oneCnt[j];
                uNum >>= 1;
            }
        }
        return result;
    }
};