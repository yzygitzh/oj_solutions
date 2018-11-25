class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap;
        int heapCount = 0;
        for (vector<int>::iterator itr = nums.begin();
             itr != nums.end(); ++itr) {
            if (heapCount < k) {
                heap.push(*itr);
                heapCount++;
            } else {
                if (heap.top() < *itr) {
                    heap.pop();
                    heap.push(*itr);
                }
            }
        }
        return heap.top();
    }
};