class Solution {
public:
    void qsort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int len = right - left + 1;
        int randIdx = left + int(double(rand()) / (RAND_MAX + 1U)) * len;
        int pivot = nums[randIdx];
        int lIdx = left, rIdx = right;
        while (lIdx <= rIdx) {
            while (nums[lIdx] < pivot) lIdx++;
            while (nums[rIdx] > pivot) rIdx--;
            if (lIdx <= rIdx) swap(nums[lIdx++], nums[rIdx--]);
        }
        qsort(nums, left, rIdx);
        qsort(nums, lIdx, right);
    }
    
    vector<int> sortArray(vector<int>& nums) {
        qsort(nums, 0, nums.size() - 1);
        return nums;
    }
};