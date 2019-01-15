class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int numsLen = nums.size();
        
        // two cases:
        // 1. > to <. in this case, last one is >, change this one to <
        //    doesn't affect the relationship before.
        // 2. the same way.
        
        for (int i = 0; i < numsLen - 1; i++) {
            if ((i % 2) && nums[i] < nums[i + 1] ||
                !(i % 2) && nums[i] > nums[i + 1]) {
                int swapTmp = nums[i];
                nums[i] = nums[i + 1];
                nums[i + 1] = swapTmp;
            }
        }
        
        return;
    }
};