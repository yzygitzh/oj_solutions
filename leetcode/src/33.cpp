class Solution {
public:    
    int search(vector<int>& nums, int target) {
        // if non-trivial rotated, left must > right
        // binary search for start index
        int numsLen = nums.size();
        if (numsLen == 0) return -1;
        int left = 0, right = numsLen - 1;
        int start = -1;
        
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            
            if (nums[left] < nums[right]) {
                // start == left
                start = left;
                break;
            } else if (nums[left] < nums[mid]) {
                // start in right region
                left = mid;
            } else {
                // start in left region
                // note that mid might be start
                right = mid;
            }
        }
        
        if (start < 0) {
            start = nums[left] < nums[right] ? left : right;
        }
        
        // normal binary search
        left = 0;
        right = numsLen - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (nums[(mid + start) % numsLen] < target) {
                left = mid;
            } else if (nums[(mid + start) % numsLen] > target) {
                right = mid;
            } else {
                return (mid + start) % numsLen;
            }
        }
        if (nums[(left + start) % numsLen] == target) {
            return (left + start) % numsLen;
        }
        if (nums[(right + start) % numsLen] == target) {
            return (right + start) % numsLen;
        }
        return -1;
    }
};