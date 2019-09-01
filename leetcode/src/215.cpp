class Solution {
public:
    void siftUp(vector<int>& nums, int idx) {
        while (idx != 0) {
            int parentIdx = (idx - 1) / 2;
            if (nums[parentIdx] > nums[idx]) {
                swap(nums[parentIdx], nums[idx]);
                idx = parentIdx;
            } else {
                break;
            }
        }
    }
    
    void siftDown(vector<int>& nums, int idx, int limit) {
        while (idx <= limit) {
            int leftIdx = idx * 2 + 1;
            int rightIdx = idx * 2 + 2;
            int minIdx = -1;
            if (leftIdx <= limit) {
                minIdx = leftIdx;
            }
            if (rightIdx <= limit && nums[rightIdx] < nums[leftIdx]) {
                minIdx = rightIdx;
            }
            if (minIdx != -1 && nums[idx] > nums[minIdx]) {
                swap(nums[idx], nums[minIdx]);
                idx = minIdx;
            } else {
                break;
            }
        }
    }
    
    int heapSelect(vector<int>& nums, int k) {
        // use min-heap
        for (int i = 0; i < nums.size(); i++) {
            if (i < k) {
                siftUp(nums, i);
            } else if (nums[i] > nums[0]) {
                swap(nums[0], nums[i]);
                siftDown(nums, 0, k - 1);
            }
        }
        return nums[0];
    }

    int findKthLargest(vector<int>& nums, int k) {
        return heapSelect(nums, k);
    }
};