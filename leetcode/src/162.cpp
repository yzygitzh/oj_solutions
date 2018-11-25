class Solution {
public:
    int safeGet(vector<int>& nums, int i) {
        if (i == -1) return nums[0];
        else if (i == nums.size()) return nums[nums.size() - 1];
        else return nums[i];
    }
    int findPeakElement(vector<int>& nums) {
        // and all interval MUST contain at least ont peak
        int numsLen = nums.size();
        if (numsLen == 1) return 0;
        
        int left = 0, right = numsLen;
        if (nums[1] < nums[0]) return 0;
        if (nums[numsLen - 2] < nums[numsLen - 1]) return numsLen - 1;
        
        while (left + 1 < right) {
            // invariant: all interval heads/tails are from here
            // 1. NOT peak
            // 2. NOT same direction (we'll choose different ones later)
            int mid = (left + right) / 2;
            if (nums[mid - 1] < nums[mid] &&
                nums[mid + 1] < nums[mid]) return mid;
            
            int leftDir = nums[left] < nums[left + 1] ? -1 : 1;
            int rightDir = nums[right - 1] < nums[right] ? -1 : 1;
            int midDir = nums[mid - 1] < nums[mid] ? -1 : 1;
            
            // obvious that three directions cannot be the same...
            // because leftDir always != rightDir
            if (leftDir != midDir) {
                right = mid;
            } else {
                left = mid;
            }
        }
        // must already return because
        // left + 1 == right and the peak cannot be left or right...
    }
};