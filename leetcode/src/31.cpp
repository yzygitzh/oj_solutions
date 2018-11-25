class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // emulate DFS stack and find next
        // _1_ ___ ___ ___
        //   ___ _3_ ___      <- last non-max
        //     ___ _4_
        //       _2_        
        
        int numsLen = nums.size();
        if (numsLen <= 1) return;
        
        int lastNonMaxIdx = -1;
        for (int i = numsLen - 1; i >= 1; i--) {
            if (nums[i - 1] < nums[i]) {
                lastNonMaxIdx = i - 1;
                break;
            }
        }
        
        if (lastNonMaxIdx == -1) {
            sort(nums.begin(), nums.end());
        } else {
            int swapIdx = numsLen - 1;
            while (nums[swapIdx] <= nums[lastNonMaxIdx]) swapIdx--;
            int swap = nums[swapIdx];
            nums[swapIdx] = nums[lastNonMaxIdx];
            nums[lastNonMaxIdx] = swap;
            sort(nums.begin() + lastNonMaxIdx + 1, nums.end());
        }
        return;
    }
};