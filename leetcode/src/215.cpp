class Solution {
public:
    void siftDown(vector<int>& nums, int idx, int limit) {
        while (true) {
            int leftIdx = idx * 2 + 1, rightIdx = idx * 2 + 2;
            int maxIdx = -1;
            if (leftIdx <= limit) {
                maxIdx = leftIdx;
            }
            if (rightIdx <= limit && nums[leftIdx] < nums[rightIdx]) {
                maxIdx = rightIdx;
            }
            if (maxIdx != -1 && nums[idx] < nums[maxIdx]) {
                swap(nums[idx], nums[maxIdx]);
                idx = maxIdx;
            } else {
                break;
            }
        }
    }
    
    void hSort(vector<int>& nums) {
        for (int i = nums.size() / 2 - 1; i >= 0; i--) {
            siftDown(nums, i, nums.size() - 1);
        }
        for (int i = nums.size() - 1; i > 0; i--) {
            swap(nums[0], nums[i]);
            siftDown(nums, 0, i - 1);
        }
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        hSort(nums);
        return nums[nums.size() - k];
    }
};