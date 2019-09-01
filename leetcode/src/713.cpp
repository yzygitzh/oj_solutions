class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int left = 0, right = 0;
        int result = 0;
        int product = 1;
        while (right < nums.size()) {
            product *= nums[right];
            right++;
            while (left < right && product >= k) {
                product /= nums[left];
                left++;
            }
            result += right - left;
        }
        return result;
    }
};