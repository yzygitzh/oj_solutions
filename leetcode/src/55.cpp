class Solution {
public:
    int getMin(int x, int y) {
        return x < y ? x : y;
    }
    
    int getMax(int x, int y) {
        return x > y ? x : y;
    }
    
    bool canJump(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return false;
        // merge intervals
        int left = 0, right = getMin(nums[0], numsLen - 1);
        
        for (int i = 0; i < numsLen; i++) {
            int currLeft = i, currRight = i + nums[i];
            if (currLeft <= right) {
                right = getMin(numsLen - 1, getMax(right, currRight));
                if (right == numsLen - 1) return true;
            } else {
                return false;
            }
        }
        return false;
    }
};