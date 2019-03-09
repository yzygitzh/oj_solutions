class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int numsLen = nums.size(), nonZeroCnt = 0;
        for (int i = 0; i < numsLen; i++) {
            if (nums[i] != 0) {
                nonZeroCnt++;
            } else if (nums[i] == 0 && i + 1 < numsLen && nums[i + 1] != 0) {
                swap(nums[nonZeroCnt], nums[i + 1]);
                nonZeroCnt++;
            }
        }
    }
};