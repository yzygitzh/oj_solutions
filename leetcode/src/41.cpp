class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return 1;
        
        for (int i = 0; i < numsLen; i++) {
            bool changed = true;
            while (changed && nums[i] > 0 && nums[i] <= numsLen &&
                   i + 1 != nums[i]) {
                int oldNum = nums[nums[i] - 1];
                changed = nums[i] != oldNum;
                nums[nums[i] - 1] = nums[i];
                nums[i] = oldNum;
            }
        }
        
        for (int i = 0; i < numsLen; i++) {
            if (i + 1 != nums[i]) return i + 1;
        }
        return numsLen + 1;
    }
};