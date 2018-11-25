class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int numsLen = nums.size();
        if (numsLen == 0) return vector<int>{-1, -1};
        
        int leftBound, rightBound;

        // find left bound
        int left = 0, right = numsLen - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (nums[mid] < target) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (nums[left] == target) {
            leftBound = left;
        } else if (nums[right] == target) {
            leftBound = right;
        } else {
            return vector<int>{-1, -1};
        }
        
        // find right bound
        left = 0, right = numsLen - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid;
            }
        }
        if (nums[right] == target) {
            rightBound = right;
        } else if (nums[left] == target) {
            rightBound = left;
        }
        
        return vector<int>{leftBound, rightBound};
    }
};