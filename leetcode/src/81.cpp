class Solution {
public:
    bool search(vector<int>& nums, int target) {
        // left (?) mid (?) right
        // (?) can be <, = or >, 9 possibilities
        
        // <<: left, <=: left, <>: right
        // =<: left, ==: unk,  =>: right
        // ><: left, >=: left, >>: not possible
        
        // 1. > means the idx is in it.
        // 2. else if left < right, then the idx is at left.
        // 3. in == case, we have to try both...
        int numsLen = nums.size();
        if (numsLen == 0) return false;
        int startIdx = searchStart(nums, 0, numsLen - 1);
        
        int left = 0, right = numsLen - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (nums[(mid + startIdx) % numsLen] < target) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (nums[(left + startIdx) % numsLen] == target) return true;
        if (nums[(right + startIdx) % numsLen] == target) return true;
        return false;
    }
    int searchStart(vector<int> &nums, int left, int right) {
        if (left + 1 >= right) {
            if (nums[left] <= nums[right]) return left;
            else return right;
        }
        int mid = (left + right) / 2;
        if (nums[left] > nums[mid]) {
            return searchStart(nums, left, mid);
        }
        if (nums[mid] > nums[right]) {
            return searchStart(nums, mid, right);
        }
        if (nums[left] < nums[right]) {
            return searchStart(nums, left, mid);
        }
        while (left < right && nums[left] == nums[right]) left++;
        return searchStart(nums, left, right);
    }
};
