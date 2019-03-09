class Solution {
public:
    void siftUp(vector<int>& nums, int idx) {
        while (true) {
            int parentIdx = (idx - 1) / 2;
            if (idx == parentIdx || nums[parentIdx] <= nums[idx]) {
                break;
            } else {
                swap(nums[parentIdx], nums[idx]);
                idx = parentIdx;
            }
        }
    }
    
    void siftDown(vector<int>& nums, int idx, int limit) {
        while (true) {
            int leftIdx = 2 * idx + 1, rightIdx = 2 * idx + 2;
            int minIdx = -1;
            if (leftIdx <= limit) {
                minIdx = leftIdx;
            }
            if (rightIdx <= limit && nums[rightIdx] < nums[leftIdx]) {
                minIdx = rightIdx;
            }
            if (minIdx == -1 || nums[idx] <= nums[minIdx]) {
                break;
            } else {
                swap(nums[idx], nums[minIdx]);
                idx = minIdx;
            }
        }
    }
    
    void minHeap(vector<int>& nums, int k) {
        for (int i = 0; i < nums.size(); i++) {
            if (i >= k && nums[0] < nums[i]) {
                // delete heap top
                swap(nums[0], nums[i]);
                siftDown(nums, 0, k - 1);
            } else if (i < k) {
                // insert element into heap
                siftUp(nums, i);
            }
        }
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        minHeap(nums, k);
        return nums[0];
    }
};