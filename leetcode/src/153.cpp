class Solution {
public:
    int findMin(vector<int>& nums) {
        // <<: <>: ><: >>:
        int numsLen = nums.size();
        int left = 0, right = numsLen - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (nums[left] > nums[mid]) {
                right = mid;
            } else if (nums[mid] > nums[right]) {
                left = mid;
            } else {
                return nums[left];
            }
        }
        return nums[left] < nums[right] ? nums[left] : nums[right];
    }
};