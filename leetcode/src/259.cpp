class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int numsLen = nums.size();
        sort(nums.begin(), nums.end());
        
        // two pointers
        int result = 0;
        for (int i = 0; i < numsLen; i++) {
            int left = i - 1, right = i + 1;
            while (left >= 0 && right < numsLen) {
                if (nums[i] + nums[left] + nums[right] < target) {
                    result += left + 1;
                    right++;
                } else {
                    left--;
                }
            }
        }
        return result;
    }
};