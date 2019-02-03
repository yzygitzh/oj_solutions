class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        int numsLen = nums.size();
        if (k == 0 || numsLen == 0) return result;

        multiset<int> minHeap, maxHeap;
        for (int i = 0; i < numsLen; i++) {
            // invariant: *minHeap.rbegin() <= *maxHeap.begin()
            // and minHeap.size() <= maxHeap.size()
            if (minHeap.size() > 0 && nums[i] <= *minHeap.rbegin()) {
                minHeap.insert(nums[i]);
            } else {
                maxHeap.insert(nums[i]);
            }
            if (i - k >= 0) {
                if (minHeap.count(nums[i - k])) {
                    minHeap.erase(minHeap.lower_bound(nums[i - k]));
                } else {
                    maxHeap.erase(maxHeap.lower_bound(nums[i - k]));
                }
            }
            while (minHeap.size() + 1 < maxHeap.size()) {
                int maxPop = *maxHeap.begin();
                maxHeap.erase(maxHeap.lower_bound(maxPop));
                minHeap.insert(maxPop);
            }
            while (minHeap.size() > maxHeap.size()) {
                int minPop = *minHeap.rbegin();
                minHeap.erase(minHeap.lower_bound(minPop));
                maxHeap.insert(minPop);
            }
            if (i + 1 >= k) {
                if (k % 2) {
                    result.push_back(*maxHeap.begin());
                } else {
                    result.push_back(((double)*minHeap.rbegin() +
                                      (double)*maxHeap.begin()) / 2);
                }
            }
        }
        return result;
    }
};