class Solution {
public:
    int findKth(vector<int>& nums, int left, int right, int k) {
        while (left < right) {
            swap(nums[right],
                 nums[left + (int)((double)rand() / (RAND_MAX + 1u)) *
                             (right - left + 1)]);
            int pivot = nums[right];
            right--;
            int lIdx = left, rIdx = right;
            while (lIdx - 1 < rIdx) {
                if (nums[lIdx] >= pivot) {
                    swap(nums[lIdx], nums[rIdx]);
                    rIdx--;
                } else {
                    lIdx++;
                }
            }
            if (k == lIdx - left + 1) {
                return pivot;
            } else if (k <= lIdx - left) {
                right = lIdx - 1;
            } else {
                k -= lIdx - left + 1;
                left = lIdx;
            }
        }
        return nums[left];
    }
    
    void wiggleSort(vector<int>& nums) {
        int numsLen = nums.size();
        int mid = findKth(nums, 0, numsLen - 1, numsLen / 2 + 1);
        // device nums into 3 parts: <mid, =mid, mid
        // put smaller number to the end
        int smallIdx = numsLen % 2 ? numsLen - 1 : numsLen - 2;
        for (int i = numsLen - 1; i >= 0; i--) {
            while (nums[i] < mid && !(i >= smallIdx && (i % 2 == 0))) {
                swap(nums[i], nums[smallIdx]);
                smallIdx -= 2;
            }
        }
        // put bigger number to the begin
        int largeIdx = 1;
        for (int i = 0; i < numsLen; i++) {
            while (nums[i] > mid && !(i <= largeIdx && (i % 2 == 1))) {
                swap(nums[i], nums[largeIdx]);
                largeIdx += 2;
            }
        }
    }
};