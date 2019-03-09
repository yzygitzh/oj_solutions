class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int numsLen = nums.size();
        int leftIdx = 0, rightIdx = 0;
        while (rightIdx < numsLen) {
            // find all duplicates
            int dupIdx = rightIdx;
            while (dupIdx < numsLen &&
                   nums[rightIdx] == nums[dupIdx]) {
                dupIdx++;
            }
            nums[leftIdx] = nums[rightIdx];
            leftIdx++;
            rightIdx = dupIdx;
        }
        return leftIdx;
    }
};