class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        if (left == right) {
            return nums.front();
        }
        right -= 2;
        if (nums[right] == nums[right + 1]) {
            return nums.back();
        }
        // invariant 1: left/right on 2*k index, k >= 0
        // invariant 2: odd/even of [left, right] keeps
        while (left / 2 + 1 < right / 2) {
            int mid = 2 * (left / 2 + (right / 2 - left / 2) / 2);
            if (nums[mid] == nums[mid + 1]) {
                left = mid + 2;
            } else {
                right = mid;
            }
        }
        if (nums[left] != nums[left + 1]) {
            return nums[left];
        } else {
            return nums[right];
        }
    }
};