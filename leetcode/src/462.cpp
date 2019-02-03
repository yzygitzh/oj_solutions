class Solution {
public:
    int getAbs(int x) {
        return x < 0 ? -x : x;
    }
    
    int minMoves2(vector<int>& nums) {
        int result = 0;
        int numsLen = nums.size();
        if (numsLen <= 1) return result;
        sort(nums.begin(), nums.end());
        if (numsLen % 2) {
            int mid = nums[numsLen / 2];
            for (int i = 0; i < numsLen; i++) {
                result += getAbs(nums[i] - mid);
            }
        } else {
            int leftResult = 0, rightResult = 0;
            int leftMid = (nums[numsLen / 2] + nums[(numsLen - 1) / 2]) / 2;
            int rightMid = (nums[numsLen / 2] + nums[(numsLen - 1) / 2] + 1) / 2;
            for (int i = 0; i < numsLen; i++) {
                leftResult += getAbs(nums[i] - leftMid);
                rightResult += getAbs(nums[i] - rightMid);
            }
            result = min(leftResult, rightResult);
        }
        return result;
    }
};