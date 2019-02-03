class Solution {
public:
    int minMoves(vector<int>& nums) {
        // equal to do minus-one's
        int result = 0;
        int numsLen = nums.size();
        if (numsLen <= 1) return 0;
        int minNum = nums[0];
        for (int i = 1; i < numsLen; i++) {
            minNum = min(minNum, nums[i]);
        }
        for (int i = 0; i < numsLen; i++) {
            result += nums[i] - minNum;
        }
        return result;
    }
};