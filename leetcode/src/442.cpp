class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        // put numbers in their place ?
        vector<int> result;
        int numsLen = nums.size();
        for (int i = 0; i < numsLen; i++) {
            if (nums[i] != i + 1) {
                bool changed = true;
                while (changed && nums[i] != i + 1) {
                    int swapTmp = nums[i];
                    nums[i] = nums[swapTmp - 1];
                    nums[swapTmp - 1] = swapTmp;
                    changed = swapTmp != nums[i];
                }
            }
        }
        for (int i = 0; i < numsLen; i++) {
            if (i + 1 != nums[i]) {
                result.push_back(nums[i]);
            }
        }
        return result;
    }
};