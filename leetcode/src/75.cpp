class Solution {
public:
    void sortColors(vector<int>& nums) {
        // fill 0 and 2
        // step only when swapping with left
        
        int numsLen = nums.size();
        if (numsLen <= 1) return;
        
        int left = 0, right = numsLen - 1;
        int setIdx = 0;

        // loop invariant: setIdx's left are all 0 or 1
        // left's left are all 0
        // right's right are all 2
        while (setIdx <= right) {
            if (nums[setIdx] == 0) {
                int swap;
                swap = nums[left];
                nums[left++] = nums[setIdx];
                nums[setIdx++] = swap;
            } else if (nums[setIdx] == 1) {
                setIdx++;
            } else if (nums[setIdx] == 2) {
                int swap;
                swap = nums[right];
                nums[right--] = nums[setIdx];
                nums[setIdx] = swap;
            }
        }
    }
};