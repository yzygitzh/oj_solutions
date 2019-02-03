class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        // for each position i, if leftMin < nums[i] < rightMax then there is one.
        int numsLen = nums.size();
        if (numsLen <= 2) return false;
        vector<int> leftMin(numsLen);
        leftMin[0] = nums[0];
        for (int i = 1; i < numsLen; i++) {
            leftMin[i] = min(nums[i], leftMin[i - 1]);
        }
        set<int> rightNumbers{nums[numsLen - 1]};
        for (int i = numsLen - 2; i > 0; i--) {
            auto itr = rightNumbers.upper_bound(leftMin[i - 1]);
            if (itr != rightNumbers.end() && *itr < nums[i]) return true;
            rightNumbers.insert(nums[i]);
        }
        return false;
    }
};