class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen <= 1) return numsLen;
        
        int newIdx = 0, oldIdx = 0, currDup = nums[0], dupCount = 0;
        while (oldIdx < numsLen) {
            if (currDup == nums[oldIdx]) {
                dupCount++;
            } else {
                currDup = nums[oldIdx];
                dupCount = 1;
            }
            if (dupCount <= 2) {
                nums[newIdx] = nums[oldIdx];
                newIdx++;
            }
            oldIdx++;
        }
        
        return newIdx;
    }
};