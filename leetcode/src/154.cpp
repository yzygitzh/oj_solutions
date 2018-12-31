class Solution {
public:
    int findMin(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        int minNum = nums[0];
        for (int i = 1; i < numsLen; i++) {
            if (nums[i] < minNum) minNum = nums[i];
        }
        return minNum;
    }
};