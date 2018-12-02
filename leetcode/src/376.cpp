class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        // deleting number doesn't produce new peak/valley
        int numsLen = nums.size();
        if (numsLen <= 1) return numsLen;
        
        int startIdx = 1;
        while (startIdx < numsLen && nums[startIdx] == nums[0]) startIdx++;
        if (startIdx == numsLen) return 1;
        bool larger = nums[startIdx] > nums[0];
        int diffCount = 0;
        for (int i = 2; i < numsLen; i++) {
            if (nums[i] == nums[i - 1]) continue;
            bool newLarger = nums[i] > nums[i - 1];
            if (larger != newLarger) {
                diffCount++;
                larger = newLarger;
            }
        }
        return diffCount + 2;
    }
};