class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int largestIdx = nums.size() - 1;
        int result = 0;
        // use nums[largestIdx], and use two pointers to find solve "two sum > nums[largestIdx]"
        while (largestIdx >= 2) {
            int left = 0, right = largestIdx - 1;
            while (left < right) {
                if (nums[left] + nums[right] > nums[largestIdx]) {
                    result += right - left;
                    right--;
                } else {
                    left++;
                }
            }
            largestIdx--;
        }
        return result;
    }
};