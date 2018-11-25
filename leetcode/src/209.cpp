class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        
        int left = 0, right = 0, sum = nums[0];
        int minLen = numsLen;
        bool found = false;
        
        while (right < numsLen) {
            int len = right - left + 1;
            if (sum >= s) {
                found = true;
                if (len < minLen) minLen = len;
                sum -= nums[left++];
                if (left > right) return minLen;
            } else {
                right++;
                if (right >= numsLen) return found ? minLen : 0;
                else sum += nums[right];
            }
        }
        return minLen;
    }
};