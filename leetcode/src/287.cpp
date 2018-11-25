class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // Floyd's algorithm for finding circle
        // Note that circle can't start at position 0
        int slowIdx = 0, fastIdx = 0;
        while (true) {
            slowIdx = nums[slowIdx];
            fastIdx = nums[nums[fastIdx]];
            if (slowIdx == fastIdx) break;
        }
        slowIdx = 0;
        while (true) {
            slowIdx = nums[slowIdx];
            fastIdx = nums[fastIdx];
            if (slowIdx == fastIdx) return slowIdx;
        }
    }
};