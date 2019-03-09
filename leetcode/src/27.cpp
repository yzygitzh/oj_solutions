class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int numsLen = nums.size();
        int leftIdx = 0, rightIdx = 0;
        while (rightIdx < numsLen) {
            if (nums[rightIdx] != val) {
                nums[leftIdx] = nums[rightIdx];
                leftIdx++;
            }
            rightIdx++;
        }
        return leftIdx;
    }
};