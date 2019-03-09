class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (nums[mid] < target) {
                left = mid;
            } else {
                right = mid;
            }
        }
        // found
        if (nums[right] == target) return right;
        else if (nums[left] == target) return left;
        // not found
        if (nums[left] > target) return left;
        else if (nums[right] < target) return right + 1;
        else return right;
    }
};