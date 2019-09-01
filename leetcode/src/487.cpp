class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int digitCnt[2] = {0};
        int left = 0, right = 0, maxCnt = 0;
        while (right < nums.size()) {
            digitCnt[nums[right]]++;
            maxCnt = max(maxCnt, digitCnt[1]);
            right++;
            while (right - left > maxCnt + 1) {
                digitCnt[nums[left]]--;
                left++;
            }
        }
        return min(int(nums.size()), maxCnt + 1);
    }
};